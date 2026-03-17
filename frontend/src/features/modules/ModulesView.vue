<template>
  <div class="modules-view">
    <Card>
      <template #title>
        <div class="flex align-items-center justify-content-between">
          <div class="flex align-items-center gap-2">
            <i class="pi pi-box text-primary" style="font-size: 1.5rem"></i>
            <span>Installierte Module</span>
            <Badge :value="totalInstances" severity="info" />
          </div>
          <div class="flex gap-2">
            <Button
              label="Zum Module Repository"
              icon="pi pi-cloud-download"
              severity="secondary"
              variant="outlined"
              @click="$router.push('/{{ module_name }}/repository')"
            />
            <Button
              v-if="hasModulesWithUpdates"
              label="Update All"
              icon="pi pi-arrow-circle-up"
              severity="primary"
              variant="outlined"
              @click="updateAllModules"
              :loading="checkingUpdates"
            />
            <Button
              label="Aktualisieren"
              icon="pi pi-refresh"
              @click="loadInstalledModules"
              :loading="loading"
            />
          </div>
        </div>
      </template>

      <template #subtitle>
        <div class="flex align-items-center gap-3 text-600">
          <span>{%- raw %}{{ totalModuleTypes }}{%- endraw %} verschiedene Module</span>
          <span>•</span>
          <span>{%- raw %}{{ totalInstances }}{%- endraw %} Instanzen</span>
        </div>
      </template>

      <template #content>
        <!-- Filters -->
        <div class="flex gap-3 mb-4">
          <span class="p-input-icon-left flex-1">
            <i class="pi pi-search" />
            <InputText 
              v-model="searchQuery" 
              placeholder="Module durchsuchen..." 
              class="w-full"
            />
          </span>
          
          <div class="flex align-items-center gap-2">
            <Checkbox v-model="showHidden" :binary="true" inputId="showHidden" />
            <label for="showHidden">Versteckte Module anzeigen</label>
          </div>
        </div>

        <!-- Data Table -->
        <DataTable 
          :value="filteredInstances" 
          :loading="loading"
          :paginator="true"
          :rows="10"
          :rowsPerPageOptions="[5, 10, 20, 50]"
          paginatorTemplate="FirstPageLink PrevPageLink PageLinks NextPageLink LastPageLink CurrentPageReport RowsPerPageDropdown"
          currentPageReportTemplate="{first} bis {last} von {totalRecords} Instanzen"
          sortField="module_name"
          :sortOrder="1"
          stripedRows
          :rowClass="rowClass"
          responsiveLayout="scroll"
        >
          <template #empty>
            <div class="text-center py-5">
              <i class="pi pi-inbox text-4xl text-400 mb-3"></i>
              <p class="text-500">Keine Module installiert</p>
            </div>
          </template>

          <Column field="module_name" header="Modulname" sortable>
            <template #body="{ data }">
              <div class="flex align-items-center gap-2">
                <i class="pi pi-box text-primary"></i>
                <span class="font-semibold">{%- raw %}{{ data.module_name }}{%- endraw %}</span>
              </div>
            </template>
          </Column>

          <Column field="instance_id" header="Instanz ID" sortable>
            <template #body="{ data }">
              <code class="text-sm">{%- raw %}{{ data.instance_id }}{%- endraw %}</code>
            </template>
          </Column>

          <Column field="template" header="Template" sortable>
            <template #body="{ data }">
              <Tag
                v-if="data.template"
                :value="data.template"
                severity="contrast"
                style="font-size: 0.7rem;"
              />
              <span v-else class="text-color-secondary text-sm">–</span>
            </template>
          </Column>

          <Column field="version" header="Version" sortable>
            <template #body="{ data }">
              <Tag :value="`v${data.version}`" severity="info" />
            </template>
          </Column>

          <Column field="status" header="Status" sortable>
            <template #body="{ data }">
              <Tag
                :value="getLivecycleStateLabel(data)"
                :severity="lifecycleSeverity[getLivecycleStateLabel(data).toLowerCase()] ?? 'secondary'"
              >
                <template #icon>
                  <i :class="['pi', getLivecycleIcon(getLivecycleStateLabel(data))]" />
                </template>
              </Tag>
            </template>
          </Column>

          <Column header="Aktionen" style="width: 16rem">
            <template #body="{ data }">
              <div class="flex gap-1 align-items-center">
                <!-- Primary star icon (multi-instance) -->
                <span v-if="getInstanceCount(data.module_name) > 1" class="mr-1">
                  <i
                    v-if="data.is_primary"
                    class="pi pi-star-fill"
                    style="font-size: 1rem; color: #f59e0b;"
                    v-tooltip.top="'Primäre Instanz'"
                  />
                  <Button
                    v-else
                    icon="pi pi-star"
                    severity="secondary"
                    size="small"
                    text
                    @click="setPrimaryInstance(data)"
                    v-tooltip.top="'Als primär setzen'"
                  />
                </span>

                <!-- Context-aware direct buttons (max 3) + overflow dropdown -->
                <template v-for="action in getDirectActions(data)" :key="action.key">
                  <!-- External link (Web Interface) -->
                  <a v-if="action.href" :href="action.href" target="_blank" rel="noopener">
                    <Button
                      :icon="action.icon"
                      :severity="action.severity"
                      :variant="action.variant"
                      size="small"
                      v-tooltip.top="action.label"
                    />
                  </a>
                  <!-- Normal action -->
                  <Button
                    v-else
                    :icon="action.icon"
                    :severity="action.severity"
                    :variant="action.variant"
                    size="small"
                    :loading="isActionLoading(data.instance_id, action.key)"
                    @click="handleAction(action.key, data)"
                    v-tooltip.top="action.label"
                  />
                </template>

                <!-- Overflow dropdown (hidden when empty) -->
                <Button
                  v-if="getOverflowActions(data).length > 0"
                  icon="pi pi-ellipsis-v"
                  severity="secondary"
                  size="small"
                  text
                  @click="(e) => showOverflowMenu(e, data)"
                  v-tooltip.top="'Weitere Aktionen'"
                />
              </div>
            </template>
          </Column>
        </DataTable>
        <!-- Single global overflow menu, reused by all rows -->
        <Menu ref="overflowMenu" :model="currentOverflowMenuItems" :popup="true" />
      </template>
    </Card>

    <!-- Instance Details Dialog -->
    <Dialog
      v-model:visible="showDetailsDialog"
      :header="`Details: ${selectedInstance?.module_name}`"
      :modal="true"
      :style="{ width: '62vw', minWidth: '520px' }"
      @show="onDetailsDialogShow"
    >
      <div v-if="selectedInstance">
        <Tabs v-model:value="detailTab">
          <TabList>
            <Tab value="info"><i class="pi pi-info-circle mr-1" />Info</Tab>
            <Tab value="functions"><i class="pi pi-play mr-1" />Funktionen</Tab>
            <Tab value="params"><i class="pi pi-sliders-h mr-1" />Parameter</Tab>
            <Tab value="volatile"><i class="pi pi-bolt mr-1" />Volatile</Tab>
            <Tab value="feeds"><i class="pi pi-rss mr-1" />Feeds</Tab>
            <Tab value="logs"><i class="pi pi-list mr-1" />Logs</Tab>
          </TabList>

          <TabPanels>
            <!-- Info Tab -->
            <TabPanel value="info">
              <div class="grid mt-2">
                <div class="col-6">
                  <div class="text-500 text-sm mb-1">Modulname</div>
                  <div class="font-semibold">{%- raw %}{{ selectedInstance.module_name }}{%- endraw %}</div>
                </div>
                <div class="col-6">
                  <div class="text-500 text-sm mb-1">Instanz ID</div>
                  <code class="text-sm">{%- raw %}{{ selectedInstance.instance_id }}{%- endraw %}</code>
                </div>
                <div class="col-6">
                  <div class="text-500 text-sm mb-1">Version</div>
                  <Tag :value="`v${selectedInstance.version}`" severity="info" />
                </div>
                <div class="col-6">
                  <div class="text-500 text-sm mb-1">Status</div>
                  <div class="flex flex-column gap-2">
                    <div class="flex align-items-center gap-2">
                      <span class="text-xs text-400 state-label-col">Lifecycle</span>
                      <Tag :value="String(detailState.lifecycle || 'unknown')" severity="secondary" />
                    </div>
                    <div class="flex align-items-center gap-2">
                      <span class="text-xs text-400 state-label-col">Operational</span>
                      <Tag :value="String(detailState.operational || 'unknown')" severity="info" />
                    </div>
                    <div class="flex align-items-center gap-2">
                      <span class="text-xs text-400 state-label-col">Health</span>
                      <Tag :value="String(detailState.health || 'unknown')" :severity="String(detailState.health || '').toUpperCase().includes('HEALTHY') ? 'success' : 'warn'" />
                    </div>
                  </div>
                </div>
                <div class="col-6">
                  <div class="text-500 text-sm mb-1">Autor</div>
                  <span class="text-sm">{%- raw %}{{ selectedInstance.author || '–' }}{%- endraw %}</span>
                </div>
              </div>
            </TabPanel>

            <!-- Functions Tab -->
            <TabPanel value="functions">
              <div v-if="detailLoading.interfaces" class="flex justify-content-center py-4">
                <ProgressSpinner style="width: 40px; height: 40px" />
              </div>
              <div v-else class="functions-tab-container mt-2">
                <!-- Function call panel (sticky) -->
                <div class="function-call-panel p-3 border-1 border-round surface-border mb-2">
                  <!-- Header: function name + mode toggle -->
                  <div class="flex align-items-center justify-content-between mb-2">
                    <div class="text-sm font-semibold">
                      <span v-if="selectedFunction">{%- raw %}{{ selectedFunction.functionname }}{%- endraw %}</span>
                      <span v-else class="text-400 text-sm font-normal">← Funktion aus der Liste auswählen</span>
                    </div>
                    <div v-if="selectedFunction" class="flex gap-1 align-items-center">
                      <Tag
                        v-if="selectedFunction.type"
                        :value="selectedFunction.type"
                        severity="secondary"
                        style="font-size:0.6rem;padding:0.1rem 0.3rem;"
                      />
                      <Button
                        :icon="functionCallMode === 'typed' ? 'pi pi-code' : 'pi pi-sliders-h'"
                        size="small"
                        text
                        @click="functionCallMode = functionCallMode === 'typed' ? 'json' : 'typed'"
                        v-tooltip.left="functionCallMode === 'typed' ? 'JSON-Modus anzeigen' : 'Felder-Modus anzeigen'"
                      />
                      <Button
                        icon="pi pi-times"
                        size="small"
                        text
                        severity="secondary"
                        @click="selectedFunction = null; callFunctionName = ''"
                        v-tooltip.left="'Auswahl aufheben'"
                      />
                    </div>
                  </div>

                  <!-- Typed mode: per-param inputs -->
                  <template v-if="selectedFunction && functionCallMode === 'typed'">
                    <div v-if="selectedFunction.params?.length" class="flex flex-column gap-2 mb-2">
                      <div
                        v-for="p in selectedFunction.params"
                        :key="p.name || p.displayname"
                        class="flex flex-column gap-1"
                      >
                        <label class="text-xs font-medium flex align-items-center gap-1">
                          {%- raw %}{{ p.name || p.displayname }}{%- endraw %}
                          <span class="text-300" style="font-size:0.65rem;">({%- raw %}{{ p.datatype }}{%- endraw %})</span>
                          <i
                            v-if="p.description"
                            class="pi pi-info-circle text-300"
                            style="font-size:0.75rem;"
                            v-tooltip.top="p.description"
                          />
                        </label>
                        <ToggleSwitch
                          v-if="isBoolType(p.datatype)"
                          v-model="typedPayload[p.name || p.displayname]"
                        />
                        <InputNumber
                          v-else-if="isNumericType(p.datatype)"
                          v-model="typedPayload[p.name || p.displayname]"
                          :useGrouping="false"
                          size="small"
                          fluid
                        />
                        <InputText
                          v-else
                          v-model="typedPayload[p.name || p.displayname]"
                          size="small"
                          fluid
                          :placeholder="p.description || (p.name || p.displayname)"
                        />
                      </div>
                    </div>
                    <div v-else class="text-xs text-400 mb-2 p-2 surface-50 border-round">
                      Keine Parameter erforderlich — direkt ausführen.
                    </div>
                  </template>

                  <!-- JSON mode: raw textarea -->
                  <template v-else-if="selectedFunction && functionCallMode === 'json'">
                    <Textarea
                      v-model="callPayloadStr"
                      rows="5"
                      class="w-full mb-2"
                      style="font-family: monospace; font-size: 0.8rem; resize: vertical;"
                      placeholder="{}"
                    />
                  </template>

                  <!-- No function selected: manual entry fallback -->
                  <template v-else>
                    <div class="flex gap-2 flex-wrap mb-2">
                      <InputText
                        v-model="callFunctionName"
                        placeholder="Funktionsname..."
                        class="flex-1"
                        size="small"
                      />
                      <InputText
                        v-model="callPayloadStr"
                        placeholder='{"key":"value"}'
                        class="flex-1"
                        size="small"
                      />
                    </div>
                  </template>

                  <Button
                    icon="pi pi-play"
                    label="Ausführen"
                    :loading="callLoading"
                    size="small"
                    @click="executeFunction"
                    :disabled="!callFunctionName && !selectedFunction"
                  />

                  <!-- Result display -->
                  <div v-if="callResult !== null" class="mt-2 p-2 surface-100 border-round">
                    <template v-if="selectedFunction?.returns?.length">
                      <div class="text-xs font-semibold mb-1 text-400">↑ Ergebnis</div>
                      <div class="flex flex-column gap-1">
                        <div
                          v-for="r in selectedFunction.returns"
                          :key="r.name || r.displayname"
                          class="flex gap-2 align-items-start"
                        >
                          <span class="text-xs text-300 flex-shrink-0" style="min-width:90px;">
                            {%- raw %}{{ r.name || r.displayname }}{%- endraw %}
                            <span class="text-200">({%- raw %}{{ r.datatype }}{%- endraw %})</span>
                          </span>
                          <code
                            class="text-xs surface-200 border-round px-1 flex-1"
                            style="overflow-wrap:anywhere; white-space:pre-wrap;"
                            v-tooltip.top="r.description || undefined"
                          >{%- raw %}{{ callResult?.[r.name || r.displayname] ?? callResult?.result ?? '—' }}{%- endraw %}</code>
                        </div>
                      </div>
                    </template>
                    <template v-else>
                      <pre class="m-0 text-xs" style="white-space: pre-wrap; max-height: 140px; overflow-y: auto;">{%- raw %}{{ JSON.stringify(callResult, null, 2) }}{%- endraw %}</pre>
                    </template>
                  </div>
                </div>
                <!-- Interface list (scrollable) -->
                <div class="function-list">
                <div v-if="detailFunctions.length === 0" class="text-center py-3 text-500">
                  <i class="pi pi-inbox text-3xl mb-2"></i>
                  <p>Keine Schnittstellen gefunden</p>
                </div>
                <div v-else class="flex flex-column gap-1">
                  <div
                    v-for="iface in detailFunctions"
                    :key="String(iface.functionname)"
                    class="p-2 surface-50 border-round border-1 border-200 mb-1"
                  >
                    <div class="flex align-items-center justify-content-between">
                      <div class="flex-1 min-w-0">
                        <div class="flex align-items-center gap-2 flex-wrap">
                          <span class="font-semibold text-sm">{%- raw %}{{ iface.functionname }}{%- endraw %}</span>
                          <Tag v-if="iface?.type" :value="iface.type" severity="secondary" style="font-size:0.6rem;padding:0.1rem 0.3rem;" />
                          <Tag
                            v-if="runningFunctions[String(iface.functionname)]"
                            value="running"
                            severity="warn"
                            style="font-size: 0.65rem;"
                          />
                        </div>
                        <!-- Parameter types -->
                        <div v-if="iface.params?.length" class="mt-1 text-xs text-400 flex gap-1 flex-wrap align-items-center">
                          <span class="text-300 mr-1" style="font-size:0.65rem;">↓ IN:</span>
                          <span v-for="(p, pi) in iface.params" :key="pi" class="inline-flex align-items-center gap-1">
                            <code class="surface-100 border-round px-1" style="font-size:0.65rem;">{%- raw %}{{ p.name || p.displayname }}{%- endraw %}</code>
                            <span class="text-300" style="font-size:0.6rem;">({%- raw %}{{ p?.datatype }}{%- endraw %})</span>
                            <span v-if="pi < (iface.params?.length ?? 0) - 1" class="text-200">,</span>
                          </span>
                        </div>
                        <!-- Return types -->
                        <div v-if="iface.returns?.length" class="mt-1 text-xs text-400 flex gap-1 flex-wrap align-items-center">
                          <span class="text-300 mr-1" style="font-size:0.65rem;">↑ OUT:</span>
                          <span v-for="(r, ri) in iface.returns" :key="ri" class="inline-flex align-items-center gap-1">
                            <code class="surface-100 border-round px-1" style="font-size:0.65rem;">{%- raw %}{{ r.name || r.displayname }}{%- endraw %}</code>
                            <span class="text-300" style="font-size:0.6rem;">({%- raw %}{{ r?.datatype }}{%- endraw %})</span>
                            <span v-if="ri < (iface.returns?.length ?? 0) - 1" class="text-200">,</span>
                          </span>
                        </div>
                      </div>
                      <div class="flex align-items-center gap-1 ml-2">
                        <Button
                          icon="pi pi-play"
                          size="small"
                          text
                          @click="selectFunction(iface)"
                          v-tooltip.left="'Auswählen & Payload befüllen'"
                        />
                        <Button
                          v-if="iface.type === 'action'"
                          icon="pi pi-times"
                          size="small"
                          text
                          severity="danger"
                          @click="cancelAction(String(iface.functionname))"
                          v-tooltip.left="'Action abbrechen'"
                        />
                      </div>
                    </div>
                  </div>
                </div>
                </div><!-- /function-list -->
              </div><!-- /functions-tab-container -->
            </TabPanel>
            <TabPanel value="params">
              <div v-if="detailLoading.params" class="flex justify-content-center py-4">
                <ProgressSpinner style="width: 40px; height: 40px" />
              </div>
              <div v-else class="mt-2">
                <!-- ── Param list ── -->
                <div v-if="Object.keys(detailParams).length === 0" class="text-center py-3 text-500">
                  <i class="pi pi-inbox text-3xl mb-2"></i>
                  <p>Keine Parameter gefunden</p>
                </div>
                <template v-else>
                  <div class="text-sm font-semibold text-500 mb-2">
                    <i class="pi pi-sliders-h mr-1" />Parameter
                  </div>
                  <div
                    v-for="(param, key) in detailParams"
                    :key="String(key)"
                    class="p-2 mb-2 surface-50 border-round border-1 border-200"
                  >
                    <!-- Name row -->
                    <div class="flex align-items-start justify-content-between gap-2 flex-wrap">
                      <div class="flex-1 min-w-0">
                        <div class="text-sm font-semibold">{%- raw %}{{ param?.displayname || key }}{%- endraw %}</div>
                        <div class="text-xs text-300 font-mono">(<code>{%- raw %}{{ key }}{%- endraw %}</code>)</div>
                        <div v-if="param?.description" class="text-xs text-400 mt-1">{%- raw %}{{ param.description }}{%- endraw %}</div>
                        <div class="text-xs text-300 mt-1">
                          Default: <code>{%- raw %}{{ JSON.stringify(param?.default_value) ?? '–' }}{%- endraw %}</code>
                        </div>
                      </div>
                      <!-- Value editor -->
                      <div class="flex align-items-center gap-1 flex-shrink-0">
                        <InputText
                          v-model="paramEditValues[String(key)]"
                          size="small"
                          class="w-8rem"
                          :placeholder="String(param?.value ?? '')"
                          :disabled="param?.editable === false"
                        />
                        <Button
                          icon="pi pi-check"
                          size="small"
                          text
                          severity="success"
                          :disabled="param?.editable === false || !(String(key) in paramEditValues)"
                          @click="saveParam(String(key))"
                          v-tooltip.left="'Wert speichern'"
                        />
                      </div>
                    </div>
                  </div>
                </template>

                <!-- ── Create form (below list, collapsible) ── -->
                <div class="mt-3 border-top-1 border-200 pt-3">
                  <Button
                    :icon="showCreateParam ? 'pi pi-minus' : 'pi pi-plus'"
                    :label="showCreateParam ? 'Formular schließen' : 'Neuen Parameter anlegen'"
                    size="small"
                    severity="secondary"
                    outlined
                    @click="showCreateParam = !showCreateParam"
                    class="w-full mb-2"
                  />
                  <div v-if="showCreateParam" class="p-3 border-1 border-round surface-border param-create-form">

                    <!-- Type selector -->
                    <div class="mb-3">
                      <div class="text-xs font-semibold text-500 mb-1">Typ *</div>
                      <div class="flex gap-1 flex-wrap">
                        <Button
                          v-for="t in ['Text', 'Zahl', 'Liste', 'Komplex']"
                          :key="t"
                          :label="t"
                          size="small"
                          :severity="newParamForm.type_ui === t ? 'primary' : 'secondary'"
                          :outlined="newParamForm.type_ui !== t"
                          @click="newParamForm.type_ui = t as any"
                        />
                      </div>
                    </div>

                    <!-- Name + DisplayName -->
                    <div class="flex gap-2 flex-wrap mb-2">
                      <div class="flex flex-column gap-1 flex-1 min-w-0" style="min-width:140px">
                        <label class="text-xs font-semibold text-500">Name *</label>
                        <InputText v-model="newParamForm.name" placeholder="my_param" size="small" fluid />
                        <small class="text-xs text-300">Nur Buchstaben, Ziffern, Unterstrich</small>
                      </div>
                      <div class="flex flex-column gap-1 flex-1 min-w-0" style="min-width:140px">
                        <label class="text-xs font-semibold text-500">Anzeigename</label>
                        <InputText v-model="newParamForm.displayname" placeholder="Mein Parameter" size="small" fluid />
                      </div>
                    </div>

                    <!-- Description -->
                    <div class="flex flex-column gap-1 mb-2">
                      <label class="text-xs font-semibold text-500">Beschreibung *</label>
                      <InputText v-model="newParamForm.description" placeholder="Kurze Beschreibung" size="small" fluid />
                    </div>

                    <!-- Default value (type-dependent) -->
                    <div class="flex flex-column gap-1 mb-2">
                      <label class="text-xs font-semibold text-500">Standardwert *</label>
                      <!-- Text -->
                      <InputText
                        v-if="newParamForm.type_ui === 'Text'"
                        v-model="newParamForm.textValue"
                        placeholder="Textwert"
                        size="small"
                        fluid
                      />
                      <!-- Zahl -->
                      <div v-else-if="newParamForm.type_ui === 'Zahl'" class="flex gap-1 align-items-center">
                        <InputText v-model="newParamForm.numberInteger" placeholder="1" size="small" class="flex-1" style="max-width:80px" />
                        <span class="text-400">.</span>
                        <InputText v-model="newParamForm.numberDecimal" placeholder="0" size="small" class="flex-1" style="max-width:80px" />
                        <span class="text-xs text-300 ml-1">{%- raw %}{{ newParamTypeName }}{%- endraw %}</span>
                      </div>
                      <!-- Liste -->
                      <div v-else-if="newParamForm.type_ui === 'Liste'" class="flex flex-column gap-1">
                        <div
                          v-for="(item, idx) in newParamForm.listItems"
                          :key="idx"
                          class="flex gap-1 align-items-center"
                        >
                          <InputText v-model="newParamForm.listItems[idx]" :placeholder="`Element ${idx + 1}`" size="small" class="flex-1" />
                          <Button icon="pi pi-minus" size="small" text severity="danger" @click="newParamForm.listItems.splice(idx, 1)" />
                        </div>
                        <Button
                          icon="pi pi-plus"
                          label="Element hinzufügen"
                          size="small"
                          text
                          @click="newParamForm.listItems.push('')"
                        />
                      </div>
                      <!-- Komplex -->
                      <Textarea
                        v-else
                        v-model="newParamForm.jsonValue"
                        rows="3"
                        class="w-full"
                        placeholder="{}"
                        style="font-family: monospace; font-size: 0.8rem;"
                      />
                    </div>

                    <!-- Visible + Editable -->
                    <div class="flex gap-4 mb-2 flex-wrap">
                      <div class="flex align-items-center gap-2">
                        <ToggleSwitch v-model="newParamForm.visible" />
                        <label class="text-xs">Sichtbar</label>
                      </div>
                      <div class="flex align-items-center gap-2">
                        <ToggleSwitch v-model="newParamForm.editable" />
                        <label class="text-xs">Bearbeitbar</label>
                      </div>
                    </div>

                    <!-- Min / Max (for Zahl or Liste) -->
                    <div v-if="newParamForm.type_ui === 'Zahl' || newParamForm.type_ui === 'Liste'" class="flex gap-2 flex-wrap mb-2">
                      <div class="flex flex-column gap-1 flex-1" style="min-width:100px">
                        <label class="text-xs text-500">{%- raw %}{{ newParamForm.type_ui === 'Liste' ? 'Min Länge' : 'Min Wert' }}{%- endraw %}</label>
                        <InputText v-model="newParamForm.min_value" placeholder="–" size="small" fluid />
                      </div>
                      <div class="flex flex-column gap-1 flex-1" style="min-width:100px">
                        <label class="text-xs text-500">{%- raw %}{{ newParamForm.type_ui === 'Liste' ? 'Max Länge' : 'Max Wert' }}{%- endraw %}</label>
                        <InputText v-model="newParamForm.max_value" placeholder="–" size="small" fluid />
                      </div>
                    </div>

                    <!-- Range (collapsible) -->
                    <div class="mb-2">
                      <button
                        class="text-xs text-400 border-none bg-transparent cursor-pointer p-0 mb-1"
                        @click.prevent="newParamForm.showRangeSection = !newParamForm.showRangeSection"
                      >
                        <i :class="newParamForm.showRangeSection ? 'pi pi-chevron-down' : 'pi pi-chevron-right'" class="mr-1" />
                        Erlaubte Werte / Typen
                      </button>
                      <div v-if="newParamForm.showRangeSection" class="flex flex-column gap-1 pl-2">
                        <div class="flex flex-column gap-1">
                          <label class="text-xs text-500">allowed_values (kommagetrennt)</label>
                          <InputText v-model="newParamForm.range_allowed_values" placeholder="val1, val2" size="small" fluid />
                        </div>
                        <div class="flex flex-column gap-1">
                          <label class="text-xs text-500">allowed_types (kommagetrennt)</label>
                          <InputText v-model="newParamForm.range_allowed_types" placeholder="string, int" size="small" fluid />
                        </div>
                      </div>
                    </div>

                    <!-- Submit -->
                    <Button
                      icon="pi pi-plus"
                      label="Parameter anlegen"
                      size="small"
                      :disabled="!newParamForm.name.trim() || !newParamForm.description.trim()"
                      @click="createParam"
                      class="w-full"
                    />
                  </div>
                </div>
              </div>
            </TabPanel>

            <TabPanel value="volatile">
              <div v-if="detailLoading.params" class="flex justify-content-center py-4">
                <ProgressSpinner style="width: 40px; height: 40px" />
              </div>
              <div v-else class="mt-2">
                <div class="p-3 border-1 border-round surface-border mb-3">
                  <div class="text-sm font-semibold mb-2">Neuen Volatile-Wert anlegen</div>
                  <div class="flex gap-2 flex-wrap">
                    <InputText v-model="newVolatileKey" placeholder="Name" class="flex-1" size="small" />
                    <InputText v-model="newVolatileValue" placeholder="Initialwert" class="flex-1" size="small" />
                    <Button
                      icon="pi pi-plus"
                      label="Anlegen"
                      size="small"
                      :disabled="!newVolatileKey.trim()"
                      @click="createVolatile"
                    />
                  </div>
                </div>
                <div v-if="Object.keys(detailVolatiles).length === 0" class="text-center py-3 text-500">
                  <i class="pi pi-inbox text-3xl mb-2"></i>
                  <p>Keine Volatile Werte gefunden</p>
                </div>
                <div
                  v-for="(vol, key) in detailVolatiles"
                  :key="String(key)"
                  class="flex align-items-center justify-content-between p-2 mb-1 surface-50 border-round border-1 border-200"
                >
                  <div class="flex-1 mr-3">
                    <div class="text-sm font-semibold">{%- raw %}{{ key }}{%- endraw %}</div>
                    <div class="text-xs text-300 mt-1">Aktuell: {%- raw %}{{ typeof vol === 'object' ? (vol?.value ?? '–') : (vol ?? '–') }}{%- endraw %}</div>
                  </div>
                  <div class="flex align-items-center gap-1">
                    <InputText
                      v-model="volatileEditValues[String(key)]"
                      size="small"
                      class="w-8rem"
                      :placeholder="String(typeof vol === 'object' ? (vol?.value ?? '') : (vol ?? ''))"
                    />
                    <Button
                      icon="pi pi-check"
                      size="small"
                      text
                      severity="success"
                      :disabled="!(String(key) in volatileEditValues)"
                      @click="saveVolatile(String(key))"
                      v-tooltip.left="'Speichern'"
                    />
                  </div>
                </div>
              </div>
            </TabPanel>
            <!-- Feeds Tab -->
            <TabPanel value="feeds">
              <div class="mt-2">
                <!-- StateFeed -->
                <div class="mb-3">
                  <div class="flex align-items-center gap-2 mb-1">
                    <span class="text-sm font-semibold">StateFeed</span>
                    <Tag :value="String(instanceStateFeeds.length)" severity="success" style="font-size:0.65rem" />
                  </div>
                  <div class="p-2 border-1 border-round surface-border font-mono" style="max-height:150px;overflow-y:auto;font-size:0.75rem;">
                    <div v-if="!instanceStateFeeds.length" class="text-400">Warte auf State-Feed Nachrichten...</div>
                    <div v-for="(f, idx) in instanceStateFeeds.slice().reverse()" :key="idx" class="mb-1">
                      <span class="text-300 mr-2">{%- raw %}{{ new Date(f.timestamp).toLocaleTimeString() }}{%- endraw %}</span>
                      <span>{%- raw %}{{ JSON.stringify(f.data) }}{%- endraw %}</span>
                    </div>
                  </div>
                </div>

                <!-- ErrorFeed -->
                <div class="mb-3">
                  <div class="flex align-items-center gap-2 mb-1">
                    <span class="text-sm font-semibold">ErrorFeed</span>
                    <Tag :value="String(instanceErrorFeeds.length)" :severity="instanceErrorFeeds.length ? 'danger' : 'secondary'" style="font-size:0.65rem" />
                  </div>
                  <div class="p-2 border-1 border-round surface-border font-mono" style="max-height:150px;overflow-y:auto;font-size:0.75rem;">
                    <div v-if="!instanceErrorFeeds.length" class="text-400">Keine Fehler empfangen.</div>
                    <div v-for="(f, idx) in instanceErrorFeeds.slice().reverse()" :key="idx" class="mb-1" style="color:#ff6b6b">
                      <span class="text-300 mr-2">{%- raw %}{{ new Date(f.timestamp).toLocaleTimeString() }}{%- endraw %}</span>
                      <span>{%- raw %}{{ f.message || JSON.stringify(f.data) }}{%- endraw %}</span>
                    </div>
                  </div>
                </div>

                <!-- NewsFeed -->
                <div class="mb-3">
                  <div class="flex align-items-center gap-2 mb-1">
                    <span class="text-sm font-semibold">NewsFeed</span>
                    <Tag :value="String(instanceNewsFeeds.length)" severity="info" style="font-size:0.65rem" />
                  </div>
                  <div class="p-2 border-1 border-round surface-border font-mono" style="max-height:150px;overflow-y:auto;font-size:0.75rem;">
                    <div v-if="!instanceNewsFeeds.length" class="text-400">Keine News empfangen.</div>
                    <div v-for="(f, idx) in instanceNewsFeeds.slice().reverse()" :key="idx" class="mb-1">
                      <span class="text-300 mr-2">{%- raw %}{{ new Date(f.timestamp).toLocaleTimeString() }}{%- endraw %}</span>
                      <span>{%- raw %}{{ f.message || JSON.stringify(f.data) }}{%- endraw %}</span>
                    </div>
                  </div>
                </div>
              </div>
            </TabPanel>

            <!-- Logs Tab -->
            <TabPanel value="logs">
              <div class="mt-2">
                <div class="flex align-items-center justify-content-between mb-2 gap-2">
                  <span class="text-sm font-semibold">Live-Logs</span>
                  <div class="flex align-items-center gap-2">
                    <Tag
                      :value="logLines.length >= 10000 ? '10000 (max)' : `${logLines.length} Zeilen`"
                      :severity="logLines.length >= 10000 ? 'warn' : 'secondary'"
                      style="font-size: 0.65rem"
                    />
                    <Button
                      icon="pi pi-trash"
                      size="small"
                      text
                      severity="secondary"
                      @click="logLines = []"
                      v-tooltip.left="'Löschen'"
                    />
                    <Button
                      :icon="logStreaming ? 'pi pi-stop-circle' : 'pi pi-play-circle'"
                      size="small"
                      text
                      :severity="logStreaming ? 'danger' : 'success'"
                      @click="toggleLogStream"
                      v-tooltip.left="logStreaming ? 'Stream stoppen' : 'Stream starten'"
                    />
                  </div>
                </div>
                <div
                  ref="logScrollContainer"
                  style="height: 380px; overflow-y: auto; background: #1e1e1e; border-radius: 6px; padding: 8px; font-family: monospace; font-size: 0.72rem;"
                >
                  <div v-if="logLines.length === 0" style="color: #666; padding: 8px;">
                    <span v-if="logNoData" style="color: #ffd93d;">
                      ⚠ Kein Log-Dienst verfügbar (get_log_history nicht implementiert oder kein Log-Traffic).
                    </span>
                    <span v-else-if="logStreaming">Warte auf Logs...</span>
                    <span v-else>Stream nicht aktiv. Starten um Logs anzuzeigen.</span>
                  </div>
                  <div
                    v-for="(line, idx) in logLines"
                    :key="idx"
                    :style="getLogLineStyle(line.level)"
                    class="mb-1"
                    style="line-height: 1.4;"
                  >
                    <span style="color: #666; margin-right: 8px;">{%- raw %}{{ line.ts }}{%- endraw %}</span>
                    <span :style="getLogLevelStyle(line.level)" style="margin-right: 8px; font-weight: bold;">[{%- raw %}{{ line.level }}{%- endraw %}]</span>
                    <span>{%- raw %}{{ line.message }}{%- endraw %}</span>
                    <span v-if="line.logger" style="color: #666; margin-left: 8px; font-size: 0.65rem;">({%- raw %}{{ line.logger }}{%- endraw %})</span>
                  </div>
                </div>
              </div>
            </TabPanel>

          </TabPanels>
        </Tabs>
      </div>
      <template #footer>
        <Button label="Schließen" icon="pi pi-times" text @click="showDetailsDialog = false" />
      </template>
    </Dialog>

    <!-- Task Progress Dialog -->
    <TaskProgressDialog
      v-if="operationStatus"
      :visible="isTracking"
      :title="progressTitle"
      :tasks="operationStatus.tasks"
      :operation-status="operationStatus.status"
      :status-message="operationStatus.message"
      :user-prompt="operationStatus.user_prompt"
      :responding-to-prompt="respondingToPrompt"
      @close="handleProgressClose"
      @cancel="handleProgressCancel"
      @prompt-response="handlePromptResponse"
    />

    <!-- Update Modal -->
    <UpdateModal
      v-if="instanceForUpdate"
      :visible="showUpdateDialog"
      :module-name="instanceForUpdate.module_name"
      :instance-id="instanceForUpdate.instance_id"
      :current-version="instanceForUpdate.version"
      :available-updates="instanceForUpdate.available_updates"
      @update:visible="showUpdateDialog = $event"
      @confirm="handleUpdateConfirm"
    />

    <!-- Delete Confirmation -->
    <ConfirmDialog />
    <Toast />
  </div>
</template>

<script setup lang="ts">
import { ref, computed, onMounted, watch, nextTick } from 'vue'
import { useConfirm } from 'primevue/useconfirm'
import { useToast } from 'primevue/usetoast'
import Card from 'primevue/card'
import DataTable from 'primevue/datatable'
import Column from 'primevue/column'
import Button from 'primevue/button'
import Menu from 'primevue/menu'
import InputText from 'primevue/inputtext'
import InputNumber from 'primevue/inputnumber'
import ToggleSwitch from 'primevue/toggleswitch'
import Textarea from 'primevue/textarea'
import Badge from 'primevue/badge'
import Tag from 'primevue/tag'
import Dialog from 'primevue/dialog'
import ConfirmDialog from 'primevue/confirmdialog'
import Toast from 'primevue/toast'
import Checkbox from 'primevue/checkbox'
import Tabs from 'primevue/tabs'
import TabList from 'primevue/tablist'
import Tab from 'primevue/tab'
import TabPanels from 'primevue/tabpanels'
import TabPanel from 'primevue/tabpanel'
import ProgressSpinner from 'primevue/progressspinner'
import TaskProgressDialog from '../../components/TaskProgressDialog.vue'
import UpdateModal from '../../components/UpdateModal.vue'
import { moduleInstanceApi } from './module.api'
import { getActionsForState, splitActions, lifecycleSeverity } from './useModuleActions'
import type { ActionItem } from './useModuleActions'
// ─── Overflow-menu (replaces SplitButton to avoid double-icon / colon artefact) ─
const overflowMenu = ref<any>(null)
const currentOverflowMenuItems = ref<any[]>([])
const showOverflowMenu = (event: Event, instance: ModuleInstance) => {
  currentOverflowMenuItems.value = getOverflowMenuItems(instance)
  overflowMenu.value?.toggle(event)
}
import { useOperationTracking } from '../../composables/useOperationTracking'
import { useModuleFeed } from '../../composables/useModuleFeed'
import type { ModuleInstance, OperationStatus, ModuleFeed } from '../../types/common'

const confirm = useConfirm()
const toast = useToast()
const {
  isTracking,
  operationStatus,
  respondingToPrompt,
  startTracking,
  stopTracking,
  respondToPrompt,
  cancelOperation
} = useOperationTracking()

// Module feed composable - für Echtzeit-Updates
const moduleFeed = useModuleFeed()

// Computed map: instance_id → latest state feed (reactive)
const latestStateByInstance = computed<Record<string, ModuleFeed>>(() => {
  const map: Record<string, ModuleFeed> = {}
  for (const feed of moduleFeed.stateFeeds.value) {
    map[feed.module_id] = feed // last one wins (feeds are ordered chronologically)
  }
  return map
})

watch(latestStateByInstance, () => {
  if (!selectedInstance.value) return
  const feed = latestStateByInstance.value[selectedInstance.value.instance_id]
  if (!feed) return
  detailState.value = {
    ...detailState.value,
    lifecycle: feed.data?.lifecycle ?? feed.data?.lifecycle_state ?? detailState.value.lifecycle,
    operational: feed.data?.operational ?? feed.data?.current ?? detailState.value.operational,
    health: feed.data?.health ?? feed.data?.health_state ?? detailState.value.health,
    timestamp: feed.timestamp,
  }
})

/** Returns the raw operational state label for display (e.g. "OPERATIONAL", "IDLE"). */
/** Returns the lifecycle state string for an instance (preferred from live feed). */
const getLivecycleStateLabel = (instance: ModuleInstance): string => {
  // 1. Prefer live WS feed
  const feed = latestStateByInstance.value[instance.instance_id]
  const lc = feed?.data?.lifecycle ?? feed?.data?.lifecycle_state
  if (lc) return String(lc).toUpperCase()

  // 2. Fallback: cached direct API state (populated after module load)
  const cached = instanceStateCache.value[instance.instance_id]
  if (cached) {
    const cachedLc = cached.lifecycle ?? cached.lifecycle_state ?? cached.current
    if (cachedLc) return String(cachedLc).toUpperCase()
  }

  // 3. Map Docker container status to a lifecycle label
  const s = (instance.status || '').toLowerCase()
  if (s === 'running') return 'ACTIVE'
  if (s === 'stopped') return 'OFFLINE'
  if (s === 'error')   return 'RECOVERING'
  return '–'
}

/** Returns the operational state string. */
const getOperationalStateLabel = (instance: ModuleInstance): string | null => {
  const feed = latestStateByInstance.value[instance.instance_id]
  const op = feed?.data?.operational ?? feed?.data?.operational_state ?? feed?.data?.current
  return op ? String(op).toUpperCase() : null
}

/** Returns the health state string. */
const getHealthStateLabel = (instance: ModuleInstance): string | null => {
  const feed = latestStateByInstance.value[instance.instance_id]
  const h = feed?.data?.health ?? feed?.data?.health_state
  return h ? String(h).toUpperCase() : null
}

/** Maps lifecycle state to a pi icon class. */
const getLivecycleIcon = (lcLabel: string): string => {
  const l = lcLabel.toLowerCase()
  if (l === 'active') return 'pi-circle-fill'
  if (l === 'offline') return 'pi-minus-circle'
  if (l === 'suspended') return 'pi-pause-circle'
  if (l === 'recovering') return 'pi-exclamation-circle'
  if (l === 'initializing') return 'pi-spinner pi-spin'
  if (l === 'shutting_down') return 'pi-power-off'
  return 'pi-question-circle'
}

// ─── Context-aware action helpers ────────────────────────────────────────────

const actionLoadingMap = ref<Record<string, boolean>>({})

const isActionLoading = (instanceId: string, actionKey: string): boolean =>
  !!actionLoadingMap.value[`${instanceId}:${actionKey}`]

const setActionLoading = (instanceId: string, actionKey: string, value: boolean) => {
  actionLoadingMap.value = {
    ...actionLoadingMap.value,
    [`${instanceId}:${actionKey}`]: value,
  }
}

const getInstanceLivecycleState = (instance: ModuleInstance): string => {
  return getLivecycleStateLabel(instance).toLowerCase()
}

const getDirectActions = (instance: ModuleInstance): ActionItem[] => {
  const lc = getInstanceLivecycleState(instance)
  const { directButtons } = splitActions(getActionsForState(lc, instance))
  return directButtons
}

const getOverflowActions = (instance: ModuleInstance): ActionItem[] => {
  const lc = getInstanceLivecycleState(instance)
  const { overflowItems } = splitActions(getActionsForState(lc, instance))
  return overflowItems
}

const getOverflowMenuItems = (instance: ModuleInstance) => {
  return getOverflowActions(instance).map(action => ({
    label: action.label,
    icon: action.icon,
    command: () => handleAction(action.key, instance),
  }))
}

/** Dispatch action key to the appropriate handler. */
const handleAction = async (key: string, instance: ModuleInstance) => {
  switch (key) {
    case 'details': showInstanceDetails(instance); break
    case 'suspend': await suspendInstance(instance); break
    case 'resume': await resumeInstance(instance); break
    case 'start': await startInstance(instance); break
    case 'stop': await stopInstance(instance); break
    case 'restart': await restartInstance(instance); break
    case 'delete': confirmDeleteInstance(instance); break
    case 'update': updateModuleInstance(instance); break
    case 'open_ui': {
      const url = instance.frontend_url ?? `/${instance.module_name}/`
      try {
        window.open(url, '_blank', 'noopener')
      } catch (e) {
        // Fallback: navigate in same tab if popup blocked
        window.location.href = url
      }
      break
    }
    default: console.warn('Unknown action:', key)
  }
}

/** Suspend a module instance (ACTIVE → SUSPENDED). */
const suspendInstance = async (instance: ModuleInstance) => {
  const key = 'suspend'
  setActionLoading(instance.instance_id, key, true)
  try {
    const result = await moduleInstanceApi.suspendInstance(instance.instance_id)
    if (result.success) {
      toast.add({ severity: 'success', summary: 'Suspended', detail: `${instance.module_name} suspended`, life: 3000 })
    } else {
      toast.add({ severity: 'warn', summary: 'Suspend failed', detail: result.message, life: 5000 })
    }
  } catch (error: any) {
    toast.add({ severity: 'error', summary: 'Error', detail: error?.message ?? 'Suspend failed', life: 5000 })
  } finally {
    setActionLoading(instance.instance_id, key, false)
  }
}

/** Resume a suspended module instance. */
const resumeInstance = async (instance: ModuleInstance) => {
  const key = 'resume'
  setActionLoading(instance.instance_id, key, true)
  try {
    const result = await moduleInstanceApi.resumeInstance(instance.instance_id)
    if (result.success) {
      toast.add({ severity: 'success', summary: 'Resumed', detail: `${instance.module_name} resumed`, life: 3000 })
    } else {
      toast.add({ severity: 'warn', summary: 'Resume failed', detail: result.message, life: 5000 })
    }
  } catch (error: any) {
    toast.add({ severity: 'error', summary: 'Error', detail: error?.message ?? 'Resume failed', life: 5000 })
  } finally {
    setActionLoading(instance.instance_id, key, false)
  }
}

const getEffectiveStatusLabel = (instance: ModuleInstance): string => {
  const feed = latestStateByInstance.value[instance.instance_id]
  if (!feed) return instance.status
  return (
    (feed.data?.operational as string) ||
    (feed.data?.current as string) ||
    feed.message ||
    instance.status
  )
}

/** Returns a normalised status key for severity / icon resolution. */
const getNormalizedStatus = (instance: ModuleInstance): string => {
  const feed = latestStateByInstance.value[instance.instance_id]
  if (!feed) return instance.status
  const opState = getEffectiveStatusLabel(instance).toUpperCase()
  if (['OPERATIONAL', 'RUNNING', 'ACTIVE'].some(s => opState.includes(s))) return 'running'
  if (['ERROR', 'FAULT'].some(s => opState.includes(s))) return 'error'
  if (['IDLE', 'STOPPED', 'STOP', 'PAUSED', 'READY', 'CONFIGURED'].some(s => opState.includes(s))) return 'idle'
  return 'unknown'
}

const searchQuery = ref('')
const showHidden = ref(false)
const loading = ref(false)
const installedModules = ref<Record<string, ModuleInstance[]>>({})
const showDetailsDialog = ref(false)
const selectedInstance = ref<ModuleInstance | null>(null)
const showUpdateDialog = ref(false)
const instanceForUpdate = ref<ModuleInstance | null>(null)
const checkingUpdates = ref(false)

// Details dialog state
const detailTab = ref('info')
const detailLoading = ref({ interfaces: false, params: false })
const detailState = ref<Record<string, any>>({})
const detailFunctions = ref<Array<Record<string, any>>>([])
const detailParams = ref<Record<string, any>>({})
const detailVolatiles = ref<Record<string, any>>({})
const paramEditValues = ref<Record<string, string>>({})
const volatileEditValues = ref<Record<string, string>>({})
const callFunctionName = ref('')
const callPayloadStr = ref('')
const callResult = ref<any>(null)
const callLoading = ref(false)
const runningFunctions = ref<Record<string, boolean>>({})
/** Currently selected function interface (set when clicking ▶ in list) */
const selectedFunction  = ref<Record<string, any> | null>(null)
/** Per-field typed payload values (used in 'typed' mode) */
const typedPayload      = ref<Record<string, any>>({})
/** 'typed' = per-field inputs, 'json' = raw JSON textarea */
const functionCallMode  = ref<'typed' | 'json'>('typed')
const newParamKey = ref('')
const newParamValue = ref('')

const showCreateParam = ref(false)
const newParamForm = ref({
  name: '',
  displayname: '',
  description: '',
  type_ui: 'Text' as 'Text' | 'Zahl' | 'Liste' | 'Komplex',
  textValue: '',
  numberInteger: '',
  numberDecimal: '',
  listItems: [] as string[],
  jsonValue: '{}',
  visible: false,
  editable: false,
  min_value: '',
  max_value: '',
  range_allowed_values: '',
  range_allowed_types: '',
  showRangeSection: false,
})

const newParamTypeName = computed((): string => {
  switch (newParamForm.value.type_ui) {
    case 'Zahl':
      return (newParamForm.value.numberDecimal && newParamForm.value.numberDecimal !== '0') ? 'float' : 'int'
    case 'Text': return 'string'
    case 'Liste': return 'list'
    case 'Komplex': return 'dict'
    default: return 'string'
  }
})

const newParamDefaultValue = computed((): unknown => {
  switch (newParamForm.value.type_ui) {
    case 'Zahl': {
      const intPart = newParamForm.value.numberInteger || '0'
      const decPart = newParamForm.value.numberDecimal || '0'
      if (decPart && decPart !== '0') return parseFloat(`${intPart}.${decPart}`)
      return parseInt(intPart, 10)
    }
    case 'Liste':
      return newParamForm.value.listItems.filter(v => v.trim() !== '')
    case 'Komplex':
      try { return JSON.parse(newParamForm.value.jsonValue || '{}') } catch { return {} }
    default:
      return newParamForm.value.textValue
  }
})
const newVolatileKey = ref('')
const newVolatileValue = ref('')

// ─── Feeds Tab state ────────────────────────────────────────────────────────
const detailFeederInterfaces = ref<Array<Record<string, any>>>([])
/** Map: functionname → EventSource (kept for potential custom-feed extensions) */
const feedEventSources = ref<Record<string, EventSource>>({})
/** Map: feedname → accumulated messages array */
const feedMessages = ref<Record<string, any[]>>({})

// ── WS-store feeds filtered to the currently selected instance ───────────────
const instanceStateFeeds = computed(() =>
  selectedInstance.value
    ? moduleFeed.stateFeeds.value.filter(f => f.module_id === selectedInstance.value!.instance_id)
    : []
)
const instanceErrorFeeds = computed(() =>
  selectedInstance.value
    ? moduleFeed.errorFeeds.value.filter(f => f.module_id === selectedInstance.value!.instance_id)
    : []
)
const instanceNewsFeeds = computed(() =>
  selectedInstance.value
    ? moduleFeed.newsFeeds.value.filter(f => f.module_id === selectedInstance.value!.instance_id)
    : []
)

// ─── Instance state cache (direct API fallback for STATUS column) ────────────
const instanceStateCache = ref<Record<string, Record<string, any>>>({})

// ─── Logs Tab state ─────────────────────────────────────────────────────────
interface LogLine { ts: string; level: string; message: string; logger?: string }
const logLines = ref<LogLine[]>([])
const logStreaming = ref(false)
const logNoData = ref(false)
const logScrollContainer = ref<HTMLElement | null>(null)
let _logEventSource: EventSource | null = null
let _logNoDataTimer: ReturnType<typeof setTimeout> | null = null

const progressTitle = computed(() => {
  if (!operationStatus.value) return 'Operation'
  
  const opType = operationStatus.value.operation_type || 'Operation'
  const moduleName = operationStatus.value.module_name || ''
  
  return moduleName ? `${opType} - ${moduleName}` : opType
})

onMounted(async () => {
  await loadInstalledModules()
  await checkForUpdates()
})

const allInstances = computed(() => {
  const instances: ModuleInstance[] = []
  
  for (const [moduleName, moduleInstances] of Object.entries(installedModules.value)) {
    for (const instance of moduleInstances) {
      instances.push({
        ...instance,
        module_name: moduleName
      })
    }
  }
  
  return instances
})

const filteredInstances = computed(() => {
  let result = allInstances.value

  if (searchQuery.value) {
    const query = searchQuery.value.toLowerCase()
    result = result.filter(i => 
      i.module_name.toLowerCase().includes(query) ||
      i.instance_id.toLowerCase().includes(query) ||
      i.version.toLowerCase().includes(query)
    )
  }

  if (!showHidden.value) {
    result = result.filter(i => i.permissions?.visible !== false)
  }

  return result
})

const totalModuleTypes = computed(() => Object.keys(installedModules.value).length)
const totalInstances = computed(() => allInstances.value.length)
const hasModulesWithUpdates = computed(() =>
  Object.values(installedModules.value).flat().some(i => i.has_updates)
)

/** Preload lifecycle states via direct API for all instances (fallback for STATUS column). */
const preloadInstanceStates = async () => {
  const all = Object.values(installedModules.value).flat()
  const results = await Promise.allSettled(
    all.map(async i => {
      const state = await moduleInstanceApi.getInstanceState(i.instance_id)
      return { id: i.instance_id, state }
    })
  )
  const cache: Record<string, Record<string, any>> = {}
  for (const r of results) {
    if (r.status === 'fulfilled') cache[r.value.id] = r.value.state
  }
  instanceStateCache.value = cache
}

const loadInstalledModules = async () => {
  try {
    loading.value = true
    installedModules.value = await moduleInstanceApi.getInstances(true)
    
    toast.add({
      severity: 'success',
      summary: 'Module geladen',
      detail: `${totalInstances.value} Instanzen gefunden`,
      life: 3000
    })
    // Silently preload lifecycle states for the STATUS column
    preloadInstanceStates()
  } catch (error) {
    console.error('Failed to load modules:', error)
    toast.add({
      severity: 'error',
      summary: 'Fehler',
      detail: 'Module konnten nicht geladen werden',
      life: 5000
    })
    installedModules.value = {}
  } finally {
    loading.value = false
  }
}

/** Trigger update dialog for all instances that have pending updates. */
const updateAllModules = async () => {
  const updatable = Object.values(installedModules.value).flat().filter(i => i.has_updates)
  if (updatable.length === 0) {
    toast.add({ severity: 'info', summary: 'Keine Updates', detail: 'Alle Module sind aktuell', life: 3000 })
    return
  }
  for (const instance of updatable) {
    if (!instance.available_updates?.length) continue
    const firstUpdate = instance.available_updates[0]
    try {
      const response = await moduleInstanceApi.updateInstance(
        instance.module_name,
        instance.instance_id,
        firstUpdate.available_version,
        {
          id: firstUpdate.repository_id,
          name: firstUpdate.repository_name,
          url: '',
          type: (firstUpdate.repository_type as 'local' | 'https') ?? 'local',
          priority: 0,
          disabled: false,
        },
        false
      )
      startTracking(response.operation_id, 'Update Module')
      toast.add({
        severity: 'info',
        summary: 'Update gestartet',
        detail: `Update von ${instance.module_name} gestartet`,
        life: 3000,
      })
    } catch (error) {
      console.error(`Failed to update ${instance.module_name}:`, error)
      toast.add({
        severity: 'error',
        summary: 'Update fehlgeschlagen',
        detail: `${instance.module_name} konnte nicht aktualisiert werden`,
        life: 5000,
      })
    }
  }
}

const checkForUpdates = async () => {
  try {
    checkingUpdates.value = true
    const updateData = await moduleInstanceApi.checkUpdates()
    
    // Map update information to instances
    for (const [instanceId, updateInfo] of Object.entries(updateData.updates_available)) {
      // Find the instance and add update information
      for (const moduleName in installedModules.value) {
        const instances = installedModules.value[moduleName]
        const instance = instances.find(i => i.instance_id === instanceId)
        if (instance) {
          instance.has_updates = true
          instance.available_updates = (updateInfo as any).available_repositories
          break
        }
      }
    }
    
    const updateCount = Object.keys(updateData.updates_available).length
    if (updateCount > 0) {
      toast.add({
        severity: 'info',
        summary: 'Updates verfügbar',
        detail: `${updateCount} Instanz(en) können aktualisiert werden`,
        life: 5000
      })
    }
  } catch (error) {
    console.error('Failed to check for updates:', error)
  } finally {
    checkingUpdates.value = false
  }
}

const updateModuleInstance = (instance: ModuleInstance) => {
  if (!instance.available_updates || instance.available_updates.length === 0) {
    toast.add({
      severity: 'warn',
      summary: 'Keine Updates',
      detail: 'Keine Updates für dieses Modul verfügbar',
      life: 3000
    })
    return
  }
  
  instanceForUpdate.value = instance
  showUpdateDialog.value = true
}

const handleUpdateConfirm = async (data: { repository: any; version: string; updateAll: boolean }) => {
  if (!instanceForUpdate.value) return
  
  const instance = instanceForUpdate.value
  
  try {
    const response = await moduleInstanceApi.updateInstance(
      instance.module_name,
      instance.instance_id,
      data.version,
      data.repository,
      data.updateAll
    )
    
    // Start tracking operation (operation_id, operationType)
    startTracking(response.operation_id, 'Update Module')
    
    toast.add({
      severity: 'info',
      summary: 'Update gestartet',
      detail: `Update von ${instance.module_name} wurde gestartet`,
      life: 3000
    })
  } catch (error) {
    console.error('Failed to start update:', error)
    toast.add({
      severity: 'error',
      summary: 'Update fehlgeschlagen',
      detail: 'Update konnte nicht gestartet werden',
      life: 5000
    })
  }
}

const showInstanceDetails = (instance: ModuleInstance) => {
  // Cleanup previous feeds/logs first
  stopFeedSubscriptions()
  stopLogStream()

  selectedInstance.value = instance
  detailTab.value = 'info'
  detailState.value = {}
  detailFunctions.value = []
  detailParams.value = {}
  detailVolatiles.value = {}
  paramEditValues.value = {}
  volatileEditValues.value = {}
  callFunctionName.value = ''
  callPayloadStr.value = ''
  callResult.value = null
  runningFunctions.value = {}
  selectedFunction.value = null
  typedPayload.value = {}
  functionCallMode.value = 'typed'
  newParamKey.value = ''
  newParamValue.value = ''
  showCreateParam.value = false
  newParamForm.value = { name: '', displayname: '', description: '', type_ui: 'Text', textValue: '', numberInteger: '', numberDecimal: '', listItems: [], jsonValue: '{}', visible: false, editable: false, min_value: '', max_value: '', range_allowed_values: '', range_allowed_types: '', showRangeSection: false }
  newVolatileKey.value = ''
  newVolatileValue.value = ''
  // Reset feeds/logs state
  detailFeederInterfaces.value = []
  feedMessages.value = {}
  feedEventSources.value = {}
  logLines.value = []
  showDetailsDialog.value = true
}

// Cleanup on dialog close
watch(showDetailsDialog, (visible) => {
  if (!visible) {
    stopFeedSubscriptions()
    stopLogStream()
  }
})

// Start feeds / logs based on active tab
watch(detailTab, async (tab) => {
  if (tab === 'feeds') {
    await startFeedSubscriptions()
  } else {
    stopFeedSubscriptions()
  }

  if (tab === 'logs') {
    startLogStream(200)
  } else {
    stopLogStream()
  }
})

const onDetailsDialogShow = () => {
  if (selectedInstance.value) {
    loadDetailState(selectedInstance.value.instance_id)
    loadDetailInterfaces(selectedInstance.value.instance_id)
    loadDetailParams(selectedInstance.value.instance_id)
  }
}

const loadDetailState = async (instanceId: string) => {
  try {
    detailState.value = await moduleInstanceApi.getInstanceState(instanceId)
  } catch (e) {
    console.warn('Could not load state:', e)
    detailState.value = {}
  }
}

const parseInterfaceList = (result: Record<string, any>): Array<Record<string, any>> => {
  const rawList = result?.interface_list || result?.interfaces || []
  const parsedList = Array.isArray(rawList)
    ? rawList
        .map((entry: any) => {
          if (typeof entry === 'string') {
            try {
              return JSON.parse(entry)
            } catch {
              return null
            }
          }
          return entry
        })
        .filter(Boolean)
    : []

  const allowedTypes = new Set(['service', 'action'])
  return parsedList.filter((entry: any) => {
    const visible = entry?.displaystyle?.visible !== false
    const callableType = allowedTypes.has(String(entry?.type || '').toLowerCase())
    return visible && callableType && !!entry?.functionname
  })
}

const loadDetailInterfaces = async (instanceId: string) => {
  detailLoading.value.interfaces = true
  try {
    const result = await moduleInstanceApi.getInstanceInterfaces(instanceId)
    detailFunctions.value = parseInterfaceList(result)
    // Parse feeder interfaces (namespace === 'feeder')
    const rawList = result?.interface_list || result?.interfaces || []
    const allInterfaces = Array.isArray(rawList)
      ? rawList.map((e: any) => (typeof e === 'string' ? JSON.parse(e) : e)).filter(Boolean)
      : []
    detailFeederInterfaces.value = allInterfaces.filter((e: any) => {
      const ns = String(e?.namespace || '').toLowerCase()
      const tp = String(e?.type || '').toLowerCase()
      // 'feeder' namespace covers StateFeed/NewsFeed/ErrorFeed; type 'message' or 'feed' is the VYRA publisher type
      return (ns === 'feeder' || tp === 'message' || tp === 'feed') && !!e?.functionname
    })
  } catch (e) {
    console.warn('Could not load interfaces:', e)
    detailFunctions.value = []
    detailFeederInterfaces.value = []
  } finally {
    detailLoading.value.interfaces = false
  }
}

// ─── Feeds helpers ──────────────────────────────────────────────────────────

/** Start feed subscriptions – standard feeds (State/Error/News) come from the
 *  singleton WS store and need no additional subscription here. */
const startFeedSubscriptions = async () => {
  stopFeedSubscriptions()
  // Standard Vyra feeds are handled by the WS store (moduleFeed).
  // Nothing to open – instanceStateFeeds / instanceErrorFeeds / instanceNewsFeeds
  // are computed from the store automatically.
}

const stopFeedSubscriptions = () => {
  for (const es of Object.values(feedEventSources.value)) {
    try { es.close() } catch { /* ignore */ }
  }
  feedEventSources.value = {}
}

// ─── Logs helpers ───────────────────────────────────────────────────────────

const MAX_LOG_LINES = 10000

const getLogLineStyle = (level: string) => {
  const l = level.toUpperCase()
  if (l === 'ERROR' || l === 'CRITICAL') return { color: '#ff6b6b' }
  if (l === 'WARNING' || l === 'WARN') return { color: '#ffd93d' }
  if (l === 'INFO') return { color: '#c3e88d' }
  return { color: '#9e9e9e' }
}

const getLogLevelStyle = (level: string) => {
  const l = level.toUpperCase()
  if (l === 'CRITICAL') return { color: '#ff4757', fontWeight: 'bold' }
  if (l === 'ERROR') return { color: '#ff6b6b' }
  if (l === 'WARNING' || l === 'WARN') return { color: '#ffd93d' }
  if (l === 'INFO') return { color: '#69db7c' }
  if (l === 'DEBUG') return { color: '#74c0fc' }
  return { color: '#888' }
}

const startLogStream = (history = 200) => {
  if (!selectedInstance.value || logStreaming.value) return
  stopLogStream()
  logStreaming.value = true
  logNoData.value = false
  // Show "no data" hint after 15 s if no log lines arrived
  _logNoDataTimer = setTimeout(() => {
    if (logLines.value.length === 0) logNoData.value = true
  }, 15_000)
  const es = moduleInstanceApi.subscribeToInstanceLogs(
    selectedInstance.value.instance_id,
    (obj: Record<string, any>) => {
      // First real data clears the "no-data" timer/flag
      logNoData.value = false
      if (_logNoDataTimer) { clearTimeout(_logNoDataTimer); _logNoDataTimer = null }
      const line: LogLine = {
        ts: obj.timestamp ? new Date(String(obj.timestamp)).toLocaleTimeString() : new Date().toLocaleTimeString(),
        level: String(obj.level || obj.levelname || 'INFO').toUpperCase(),
        message: String(obj.message || obj.msg || JSON.stringify(obj)),
        logger: obj.name || obj.logger,
      }
      logLines.value = [...logLines.value.slice(-(MAX_LOG_LINES - 1)), line]
      nextTick(() => {
        if (logScrollContainer.value) {
          logScrollContainer.value.scrollTop = logScrollContainer.value.scrollHeight
        }
      })
    },
    history
  )
  es.onerror = () => {
    logStreaming.value = false
    if (_logNoDataTimer) { clearTimeout(_logNoDataTimer); _logNoDataTimer = null }
  }
  _logEventSource = es
}

const stopLogStream = () => {
  if (_logNoDataTimer) { clearTimeout(_logNoDataTimer); _logNoDataTimer = null }
  if (_logEventSource) {
    try { _logEventSource.close() } catch { /* ignore */ }
    _logEventSource = null
  }
  logStreaming.value = false
  logNoData.value = false
}

/** Select a function and pre-fill the JSON payload template from its param definitions. */
// ─── Typed call helpers ─────────────────────────────────────────────────────

const isBoolType = (dt: string): boolean => {
  const t = String(dt ?? '').toLowerCase()
  return t === 'bool' || t === 'boolean'
}

const isNumericType = (dt: string): boolean => {
  const t = String(dt ?? '').toLowerCase()
  return (
    t.startsWith('int') || t.startsWith('uint') ||
    t === 'float' || t === 'double' ||
    t === 'float32' || t === 'float64' ||
    t === 'int32' || t === 'int64' || t === 'uint32' || t === 'uint64'
  )
}

const selectFunction = (iface: Record<string, any>) => {
  selectedFunction.value = iface
  callFunctionName.value = String(iface.functionname)
  functionCallMode.value = 'typed'
  const params: any[] = Array.isArray(iface.params) ? iface.params : []
  if (params.length > 0) {
    const template: Record<string, any> = {}
    const typed: Record<string, any> = {}
    for (const p of params) {
      const key = p.name || p.displayname || 'param'
      const type = String(p.datatype || '').toLowerCase()
      let defaultVal: any
      if (isBoolType(type))         defaultVal = false
      else if (isNumericType(type)) defaultVal = 0
      else if (type.endsWith('[]')) defaultVal = []
      else                          defaultVal = ''
      template[key] = defaultVal
      typed[key]    = defaultVal
    }
    typedPayload.value    = typed
    callPayloadStr.value  = JSON.stringify(template, null, 2)
  } else {
    typedPayload.value   = {}
    callPayloadStr.value = '{}'
  }
}

const toggleLogStream = () => {
  if (logStreaming.value) {
    stopLogStream()
  } else {
    startLogStream(200)
  }
}

const normalizeParamMap = (input: any): Record<string, any> => {
  if (Array.isArray(input)) {
    return input.reduce((acc: Record<string, any>, entry: any) => {
      const key = entry?.name || entry?.key
      if (key) {
        acc[String(key)] = entry
      }
      return acc
    }, {})
  }
  return input && typeof input === 'object' ? input : {}
}

const loadDetailParams = async (instanceId: string) => {
  detailLoading.value.params = true
  try {
    const [paramsResult, volsResult] = await Promise.allSettled([
      moduleInstanceApi.getInstanceParams(instanceId),
      moduleInstanceApi.getInstanceVolatiles(instanceId)
    ])
    if (paramsResult.status === 'fulfilled') {
      const raw = paramsResult.value?.all_params_json
      const parsed = raw ? JSON.parse(raw) : (paramsResult.value ?? {})
      detailParams.value = normalizeParamMap(parsed)
    }
    if (volsResult.status === 'fulfilled') {
      const raw = volsResult.value?.all_volatiles_json
      const parsed = raw ? JSON.parse(raw) : (volsResult.value ?? {})
      detailVolatiles.value = normalizeParamMap(parsed)
    }
  } catch (e) {
    console.warn('Could not load params/volatiles:', e)
  } finally {
    detailLoading.value.params = false
  }
}

const executeFunction = async () => {
  const fnName = callFunctionName.value || String(selectedFunction.value?.functionname ?? '')
  if (!selectedInstance.value || !fnName) return
  if (callFunctionName.value !== fnName) callFunctionName.value = fnName
  runningFunctions.value[fnName] = true
  callLoading.value = true
  callResult.value = null
  try {
    let payload: Record<string, any> = {}
    if (functionCallMode.value === 'typed' && selectedFunction.value) {
      payload = { ...typedPayload.value }
    } else if (callPayloadStr.value.trim()) {
      payload = JSON.parse(callPayloadStr.value)
    }
    callResult.value = await moduleInstanceApi.callInstanceFunction(
      selectedInstance.value.instance_id,
      fnName,
      payload
    )
  } catch (e: any) {
    callResult.value = { error: e?.message ?? String(e) }
  } finally {
    runningFunctions.value[fnName] = false
    callLoading.value = false
  }
}

const cancelAction = async (functionName: string) => {
  if (!selectedInstance.value) return
  const cancelFunctionName = `${functionName}_cancel`
  try {
    const result = await moduleInstanceApi.callInstanceFunction(
      selectedInstance.value.instance_id,
      cancelFunctionName,
      {}
    )
    callResult.value = result
    toast.add({ severity: 'info', summary: 'Action', detail: `Cancel für '${functionName}' gesendet`, life: 3000 })
  } catch (e: any) {
    toast.add({ severity: 'warn', summary: 'Cancel nicht verfügbar', detail: `Keine cancel-Funktion für '${functionName}'`, life: 4000 })
  }
}

const saveParam = async (key: string) => {
  if (!selectedInstance.value) return
  const value = paramEditValues.value[key]
  if (!(key in paramEditValues.value)) return
  try {
    await moduleInstanceApi.setInstanceParam(selectedInstance.value.instance_id, key, value)
    toast.add({ severity: 'success', summary: 'Gespeichert', detail: `Parameter '${key}' aktualisiert`, life: 3000 })
    paramEditValues.value[key] = ''
    await loadDetailParams(selectedInstance.value.instance_id)
  } catch (e) {
    toast.add({ severity: 'error', summary: 'Fehler', detail: `Konnte '${key}' nicht setzen`, life: 4000 })
  }
}

const saveVolatile = async (key: string) => {
  if (!selectedInstance.value) return
  const value = volatileEditValues.value[key]
  if (!(key in volatileEditValues.value)) return
  try {
    await moduleInstanceApi.setInstanceVolatile(selectedInstance.value.instance_id, key, value)
    toast.add({ severity: 'success', summary: 'Gespeichert', detail: `Volatile '${key}' aktualisiert`, life: 3000 })
    volatileEditValues.value[key] = ''
    await loadDetailParams(selectedInstance.value.instance_id)
  } catch (e) {
    toast.add({ severity: 'error', summary: 'Fehler', detail: `Konnte '${key}' nicht setzen`, life: 4000 })
  }
}

const createParam = async () => {
  if (!selectedInstance.value || !newParamForm.value.name.trim()) return
  const rangeValue: Record<string, unknown> | null = (
    newParamForm.value.range_allowed_values.trim() || newParamForm.value.range_allowed_types.trim()
  ) ? {
    ...(newParamForm.value.range_allowed_values.trim()
      ? { allowed_values: newParamForm.value.range_allowed_values.split(',').map(s => s.trim()).filter(Boolean) }
      : {}),
    ...(newParamForm.value.range_allowed_types.trim()
      ? { allowed_types: newParamForm.value.range_allowed_types.split(',').map(s => s.trim()).filter(Boolean) }
      : {}),
  } : null
  try {
    const result = await moduleInstanceApi.createInstanceParamFull(
      selectedInstance.value.instance_id,
      {
        name: newParamForm.value.name.trim(),
        default_value: newParamDefaultValue.value,
        type: newParamTypeName.value,
        description: newParamForm.value.description,
        displayname: newParamForm.value.displayname.trim() || undefined,
        visible: newParamForm.value.visible,
        editable: newParamForm.value.editable,
        min_value: newParamForm.value.min_value.trim() || null,
        max_value: newParamForm.value.max_value.trim() || null,
        range_value: rangeValue,
      }
    )
    if (result?.success === false) {
      toast.add({ severity: 'warn', summary: 'Fehler', detail: result.message || 'Parameter konnte nicht erstellt werden', life: 5000 })
      return
    }
    toast.add({ severity: 'success', summary: 'Angelegt', detail: `Parameter '${newParamForm.value.name}' erstellt`, life: 3000 })
    newParamForm.value = { name: '', displayname: '', description: '', type_ui: 'Text', textValue: '', numberInteger: '', numberDecimal: '', listItems: [], jsonValue: '{}', visible: false, editable: false, min_value: '', max_value: '', range_allowed_values: '', range_allowed_types: '', showRangeSection: false }
    showCreateParam.value = false
    if (selectedInstance.value) await loadDetailParams(selectedInstance.value.instance_id)
  } catch (e: unknown) {
    const msg = e instanceof Error ? e.message : 'Unbekannter Fehler'
    toast.add({ severity: 'error', summary: 'Fehler', detail: msg, life: 4000 })
  }
}

const createVolatile = async () => {
  if (!selectedInstance.value || !newVolatileKey.value.trim()) return
  try {
    await moduleInstanceApi.createInstanceVolatile(
      selectedInstance.value.instance_id,
      newVolatileKey.value.trim(),
      newVolatileValue.value
    )
    toast.add({ severity: 'success', summary: 'Angelegt', detail: `Volatile '${newVolatileKey.value}' erstellt`, life: 3000 })
    newVolatileKey.value = ''
    newVolatileValue.value = ''
    await loadDetailParams(selectedInstance.value.instance_id)
  } catch (e) {
    toast.add({ severity: 'error', summary: 'Fehler', detail: 'Volatile konnte nicht erstellt werden', life: 4000 })
  }
}

const canStopInstance = (instance: ModuleInstance) => {
  const normalized = getNormalizedStatus(instance)
  return normalized === 'running'
}

const canStartInstance = (instance: ModuleInstance) => {
  const normalized = getNormalizedStatus(instance)
  return normalized === 'idle' || normalized === 'error' || normalized === 'unknown'
}

const getInstanceCount = (moduleName: string): number => {
  const instances = installedModules.value[moduleName] || []
  return instances.length
}

const openFrontend = (frontendUrl: string) => {
  if (frontendUrl) {
    window.open(frontendUrl, '_blank')
  }
}

const setPrimaryInstance = (instance: ModuleInstance) => {
  confirm.require({
    message: `${instance.module_name} (${instance.instance_id}) als primäre Instanz setzen? Diese wird unter /${instance.module_name}/ erreichbar sein.`,
    header: 'Primäre Instanz setzen',
    icon: 'pi pi-star',
    acceptLabel: 'Als primär setzen',
    rejectLabel: 'Abbrechen',
    accept: async () => {
      try {
        const response = await moduleInstanceApi.setPrimaryInstance(
          instance.module_name,
          instance.instance_id
        )
        
        // Konvertiere OperationResponse zu OperationStatus für initialStatus
        const initialStatus: OperationStatus = {
          operation_id: response.operation_id,
          operation_type: response.operation_type,
          module_name: response.module_name,
          status: response.status as any,
          message: response.message,
          progress: response.progress,
          tasks: response.tasks,
          current_task_id: undefined,
          user_prompt: undefined,
          error: response.error || undefined,
          result: undefined
        }
        
        await startTracking(response.operation_id, `Setze primäre Instanz: ${instance.module_name}`, {
          statusUrl: response.status_url,
          onComplete: loadInstalledModules,
          initialStatus
        })
      } catch (error) {
        console.error('Set primary failed:', error)
        toast.add({
          severity: 'error',
          summary: 'Fehler',
          detail: 'Primäre Instanz konnte nicht gesetzt werden',
          life: 5000
        })
      }
    }
  })
}

const restartInstance = async (instance: ModuleInstance) => {
  try {
    const response = await moduleInstanceApi.restartInstance(instance.instance_id)
    
    const initialStatus: OperationStatus = {
      operation_id: response.operation_id,
      operation_type: response.operation_type,
      module_name: response.module_name,
      status: response.status as any,
      message: response.message,
      progress: response.progress,
      tasks: response.tasks,
      current_task_id: undefined,
      user_prompt: undefined,
      error: response.error || undefined,
      result: undefined
    }
    
    await startTracking(response.operation_id, `Neustart: ${instance.module_name}`, {
      statusUrl: response.status_url,
      onComplete: loadInstalledModules,
      initialStatus
    })
    
    toast.add({
      severity: 'info',
      summary: 'Neustart gestartet',
      detail: `${instance.module_name} wird neu gestartet`,
      life: 3000
    })
  } catch (error) {
    console.error('Restart failed:', error)
    toast.add({
      severity: 'error',
      summary: 'Neustart fehlgeschlagen',
      detail: 'Instanz konnte nicht neu gestartet werden',
      life: 5000
    })
  }
}

const stopInstance = async (instance: ModuleInstance) => {
  confirm.require({
    message: `${instance.module_name} wirklich stoppen? Die Instanz wird deaktiviert.`,
    header: 'Instanz stoppen',
    icon: 'pi pi-pause-circle',
    acceptLabel: 'Stoppen',
    rejectLabel: 'Abbrechen',
    acceptClass: 'p-button-warning',
    accept: async () => {
      try {
        const response = await moduleInstanceApi.stopInstance(instance.instance_id)
        
        const initialStatus: OperationStatus = {
          operation_id: response.operation_id,
          operation_type: response.operation_type,
          module_name: response.module_name,
          status: response.status as any,
          message: response.message,
          progress: response.progress,
          tasks: response.tasks,
          current_task_id: undefined,
          user_prompt: undefined,
          error: response.error || undefined,
          result: undefined
        }
        
        await startTracking(response.operation_id, `Stoppe ${instance.module_name}`, {
          statusUrl: response.status_url,
          onComplete: loadInstalledModules,
          initialStatus
        })
        
        toast.add({
          severity: 'info',
          summary: 'Instanz gestoppt',
          detail: `${instance.module_name} wurde gestoppt`,
          life: 3000
        })
      } catch (error) {
        console.error('Stop failed:', error)
        toast.add({
          severity: 'error',
          summary: 'Stoppen fehlgeschlagen',
          detail: 'Instanz konnte nicht gestoppt werden',
          life: 5000
        })
      }
    }
  })
}

const startInstance = async (instance: ModuleInstance) => {
  try {
    const response = await moduleInstanceApi.startInstance(instance.instance_id)
    
    const initialStatus: OperationStatus = {
      operation_id: response.operation_id,
      operation_type: response.operation_type,
      module_name: response.module_name,
      status: response.status as any,
      message: response.message,
      progress: response.progress,
      tasks: response.tasks,
      current_task_id: undefined,
      user_prompt: undefined,
      error: response.error || undefined,
      result: undefined
    }
    
    await startTracking(response.operation_id, `Starte ${instance.module_name}`, {
      statusUrl: response.status_url,
      onComplete: loadInstalledModules,
      initialStatus
    })
    
    toast.add({
      severity: 'info',
      summary: 'Instanz gestartet',
      detail: `${instance.module_name} wurde gestartet`,
      life: 3000
    })
  } catch (error) {
    console.error('Start failed:', error)
    toast.add({
      severity: 'error',
      summary: 'Starten fehlgeschlagen',
      detail: 'Instanz konnte nicht gestartet werden',
      life: 5000
    })
  }
}

const confirmDeleteInstance = (instance: ModuleInstance) => {
  confirm.require({
    message: `${instance.module_name} (${instance.instance_id}) wirklich löschen? Dies kann nicht rückgängig gemacht werden.`,
    header: 'Löschen bestätigen',
    icon: 'pi pi-exclamation-triangle',
    acceptLabel: 'Löschen',
    rejectLabel: 'Abbrechen',
    acceptClass: 'p-button-danger',
    accept: async () => {
      try {
        const response = await moduleInstanceApi.deleteInstance(instance.instance_id)
        
        // Konvertiere OperationResponse zu OperationStatus für initialStatus
        const initialStatus: OperationStatus = {
          operation_id: response.operation_id,
          operation_type: response.operation_type,
          module_name: response.module_name,
          status: response.status as any,
          message: response.message,
          progress: response.progress,
          tasks: response.tasks,
          current_task_id: undefined,
          user_prompt: undefined,
          error: response.error || undefined,
          result: undefined
        }
        
        await startTracking(response.operation_id, `Lösche ${instance.module_name}`, {
          statusUrl: response.status_url,
          onComplete: loadInstalledModules,
          initialStatus
        })
      } catch (error) {
        console.error('Delete failed:', error)
        toast.add({
          severity: 'error',
          summary: 'Löschen fehlgeschlagen',
          detail: 'Modul konnte nicht gelöscht werden',
          life: 5000
        })
      }
    }
  })
}

const getStatusSeverity = (status: string) => {
  const severityMap: Record<string, string> = {
    running: 'success',
    stopped: 'warn',
    idle: 'info',
    error: 'danger',
    unknown: 'secondary'
  }
  return severityMap[status] || 'info'
}

const getStatusIcon = (status: string) => {
  const iconMap: Record<string, string> = {
    running: 'pi-play-circle',
    stopped: 'pi-pause-circle',
    idle: 'pi-clock',
    error: 'pi-times-circle',
    unknown: 'pi-question-circle'
  }
  return iconMap[status] || 'pi-info-circle'
}

const rowClass = (data: ModuleInstance) => {
  return data.permissions?.visible === false ? 'hidden-module-row' : ''
}

const handleProgressClose = () => {
  stopTracking()
}

const handleProgressCancel = () => {
  cancelOperation()
}

const handlePromptResponse = (promptId: string, response: string) => {
  respondToPrompt(promptId, response)
}
</script>

<style scoped>
.modules-view {
  animation: fadeIn 0.3s ease-in;
}

@keyframes fadeIn {
  from { opacity: 0; transform: translateY(20px); }
  to { opacity: 1; transform: translateY(0); }
}

:deep(.hidden-module-row) {
  opacity: 0.5;
  background-color: rgba(0, 0, 0, 0.02);
}

:deep(.hidden-module-row:hover) {
  opacity: 0.7;
}

/* ── State label column ── */
.state-label-col {
  min-width: 5.5rem;
  flex-shrink: 0;
}

/* ── Functions tab ── */
.functions-tab-container {
  display: flex;
  flex-direction: column;
  max-height: 62vh;
  overflow: hidden;
}

.function-call-panel {
  flex-shrink: 0;
  position: sticky;
  top: 0;
  z-index: 2;
  background: var(--p-surface-card, var(--surface-card, #ffffff));
}

.function-list {
  overflow-y: auto;
  flex: 1;
  min-height: 0;
  padding-bottom: 0.5rem;
}

/* ── Param create form ── */
.param-create-form {
  animation: fadeIn 0.15s ease-in;
}

/* ── Mobile responsive ── */
@media (max-width: 640px) {
  :deep(.p-dialog) {
    width: 98vw !important;
    max-width: 98vw !important;
    margin: 0.5rem !important;
  }

  :deep(.p-tablist) {
    overflow-x: auto;
    -webkit-overflow-scrolling: touch;
  }

  :deep(.p-tablist .p-tab) {
    white-space: nowrap;
    padding: 0.4rem 0.6rem;
    font-size: 0.8rem;
  }

  .functions-tab-container {
    max-height: 55vh;
  }

  .param-create-form .flex.gap-2.flex-wrap > * {
    flex: 1 1 100%;
    min-width: 0;
  }
}

@media (max-width: 480px) {
  :deep(.p-datatable .p-datatable-tbody > tr > td) {
    padding: 0.4rem 0.3rem;
    font-size: 0.8rem;
  }

  :deep(.p-datatable .p-datatable-thead > tr > th) {
    padding: 0.4rem 0.3rem;
    font-size: 0.75rem;
  }
}
</style>
