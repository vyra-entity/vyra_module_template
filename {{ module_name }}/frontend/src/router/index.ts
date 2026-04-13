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
    path: '/{{ module_name }}/settings',
    name: 'settings',
    component: () => import('../features/settings/SettingsView.vue'),
    meta: {
      title: 'Einstellungen - {{ module_display_name }}',
      requiresAuth: true,
      sidebarGroup: 'settings',
      sidebarPriority: 50,
      sidebarIcon: 'pi pi-cog',
    }
  },
  {
    path: '/{{ module_name }}/p/:pluginSlug',
    name: 'plugin-page',
    component: () => import('../features/plugins/PluginPageView.vue'),
    meta: {
      title: 'Plugin Page - {{ module_display_name }}',
      requiresAuth: true,
    },
  },

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
