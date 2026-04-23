/*!
 * coi-serviceworker v0.1.7 — MIT License
 * https://github.com/gzuidhof/coi-serviceworker
 *
 * Enables cross-origin isolation on static sites (e.g. GitHub Pages) by
 * registering a service worker that adds Cross-Origin-Opener-Policy and
 * Cross-Origin-Embedder-Policy headers. Cross-origin isolation is required
 * to use SharedArrayBuffer — which FFmpeg.wasm relies on.
 */
/*global clients, self */
'use strict';
(() => {
  if (typeof window === 'undefined') {
    // ===== Service worker context =====
    self.addEventListener('install', () => self.skipWaiting());
    self.addEventListener('activate', (e) => e.waitUntil(self.clients.claim()));
    self.addEventListener('message', (e) => {
      if (!e.data) return;
      if (e.data.type === 'deregister') {
        self.registration.unregister()
          .then(() => self.clients.matchAll())
          .then((clients) => clients.forEach((c) => c.navigate(c.url)));
      }
    });
    self.addEventListener('fetch', (event) => {
      const req = event.request;
      if (req.cache === 'only-if-cached' && req.mode !== 'same-origin') return;
      event.respondWith(
        fetch(req)
          .then((response) => {
            if (response.status === 0) return response;
            const headers = new Headers(response.headers);
            headers.set('Cross-Origin-Embedder-Policy', 'credentialless');
            headers.set('Cross-Origin-Opener-Policy', 'same-origin');
            return new Response(response.body, {
              status: response.status,
              statusText: response.statusText,
              headers,
            });
          })
          .catch((e) => console.error('coi-serviceworker fetch:', e))
      );
    });
  } else {
    // ===== Page context =====
    const n = navigator;
    if (window.crossOriginIsolated !== false) return;
    if (!window.isSecureContext) {
      console.log('[COI] Insecure context — cross-origin isolation unavailable.');
      return;
    }
    if (!n.serviceWorker) {
      console.log('[COI] Service workers not supported.');
      return;
    }
    const script = document.currentScript;
    const swUrl = script && script.src ? script.src : 'coi-serviceworker.js';
    n.serviceWorker.register(swUrl, { scope: './' }).then(
      (registration) => {
        console.log('[COI] Registered — scope:', registration.scope);
        registration.addEventListener('updatefound', () => {
          console.log('[COI] Update found — reloading.');
          window.location.reload();
        });
        if (registration.active && !n.serviceWorker.controller) {
          console.log('[COI] Controller missing — reloading to activate.');
          window.location.reload();
        }
      },
      (err) => console.log('[COI] Registration failed:', err)
    );
  }
})();
