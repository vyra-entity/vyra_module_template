import { createRouter, createWebHistory, type RouteRecordRaw } from 'vue-router'
import { useAuthStore } from '../store/auth'

const routes: RouteRecordRaw[] = [
  {
    path: '/{{ module_name }}',
    redirect: '/{{ module_name }}/home'
  },
  {
    path: '/{{ module_name }}/login',
    name: 'login',
    component: () => import('../features/auth/LoginView.vue'),
    meta: {
      title: 'Login - {{ module_display_name }}',
      requiresAuth: false,
    }
  },
  {
    path: '/{{ module_name }}/home',
    name: 'home',
    component: () => import('../features/home/HomeView.vue'),
    meta: {
      title: 'Home - {{ module_display_name }}',
      requiresAuth: true,
      sidebarGroup: 'main',
      sidebarPriority: 100,
      sidebarIcon: 'pi pi-home',
    }
  },
  {
    path: '/{{ module_name }}/modules',
    name: 'modules',
    component: () => import('../features/modules/ModulesView.vue'),
    meta: {
      title: 'Installierte Module - {{ module_display_name }}',
      requiresAuth: true,
      sidebarGroup: 'main',
      sidebarPriority: 90,
      sidebarIcon: 'pi pi-box',
    }
  },
  {
    path: '/{{ module_name }}/repository',
    name: 'repository',
    component: () => import('../features/repository/RepositoryView.vue'),
    meta: {
      title: 'Module Repository - {{ module_display_name }}',
      requiresAuth: true,
      sidebarGroup: 'main',
      sidebarPriority: 80,
      sidebarIcon: 'pi pi-cloud-download',
    }
  },
  {
    path: '/{{ module_name }}/plugins',
    name: 'plugins',
    component: () => import('../features/plugins/PluginRepositoryView.vue'),
    meta: {
      title: 'Plugin Repository - {{ module_display_name }}',
      requiresAuth: true,
      sidebarGroup: 'main',
      sidebarPriority: 75,
      sidebarIcon: 'pi pi-puzzle',
    }
  },
  {
    path: '/{{ module_name }}/installed-plugins',
    name: 'installed-plugins',
    component: () => import('../features/plugin_admin_service/InstalledPluginsView.vue'),
    meta: {
      title: 'Installierte Plugins - {{ module_display_name }}',
      requiresAuth: true,
      sidebarGroup: 'main',
      sidebarPriority: 73,
      sidebarIcon: 'pi pi-th-large',
      sidebarLabel: 'Plugins',
    }
  },
  {
    path: '/{{ module_name }}/monitoring',
    name: 'monitoring',
    component: () => import('../features/monitoring/MonitoringView.vue'),
    meta: {
      title: 'System Monitoring - {{ module_display_name }}',
      requiresAuth: true,
      sidebarGroup: 'analysis',
      sidebarPriority: 100,
      sidebarIcon: 'pi pi-chart-line',
    }
  }
]

const router = createRouter({
  history: createWebHistory(),
  routes
})

// Authentication guard
router.beforeEach(async (to, from, next) => {
  const authStore = useAuthStore()
  
  // Set page title
  document.title = (to.meta.title as string) || '{{ module_display_name }}'
  
  // Check if route requires authentication
  const requiresAuth = to.meta.requiresAuth !== false // Default to true if not specified
  
  // If route doesn't require auth, allow access
  if (!requiresAuth) {
    next()
    return
  }
  
  // Verify authentication status
  if (!authStore.isAuthenticated) {
    const isValid = await authStore.verifyAuth()
    
    if (!isValid) {
      // Not authenticated, redirect to login
      next({ name: 'login', query: { redirect: to.fullPath } })
      return
    }
  }
  
  // Authenticated, allow access
  next()
})

export default router
