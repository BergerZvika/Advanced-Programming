# HTML Tutorial

A practical HTML tutorial organized into 15 topic folders, each with standalone HTML files you can open directly in a browser. An interactive `lab.html` ships every step with a live editor + preview.

The folder numbering matches the topic order in `lab.html` — open folder `N` and you'll find the files for topic `N` in the lab.

## Structure

### 1. Hello HTML
The simplest possible complete page — your first HTML.

| File | Topic |
|------|-------|
| `hello_html.html` | DOCTYPE, `<html>`, `<head>`, `<title>`, `<body>`, a heading, a paragraph |

### 2. Text
Text content and inline formatting.

| File | Topic |
|------|-------|
| `headings-paragraphs.html` | `<h1>`–`<h6>`, `<p>`, `<br>`, `<hr>`, `<pre>` |
| `links.html` | `<a>`, href types (absolute, relative, anchor, mailto, tel), `target`, `rel` |
| `lists.html` | `<ul>`, `<ol>` (with type/start/reversed), nested lists, `<dl>` |
| `quotations.html` | `<blockquote>`, `<q>`, `<cite>`, `<abbr>`, `<bdo>`, `<address>` |
| `inline-text.html` | `<strong>`, `<em>`, `<mark>`, `<code>`, `<kbd>`, `<abbr>`, `<sub>`, `<sup>`, `<del>`, `<ins>`, and more |
| `entities-symbols.html` | HTML entities: `&amp;`, `&lt;`, `&nbsp;`, `&copy;`, arrows, Greek, math, currency |

### 3. Buttons
Clickable interactivity — from a single inline `onclick` to buttons driving cross-page navigation.

| File | Topic |
|------|-------|
| `button.html` | Button with inline JS — toggle page background on click |
| `button_file.html` + `button_script.js` | Same button, JS moved to an external file via `<script src="...">` |
| `first.html` + `second.html` | Navigate between two pages via `location.href` |

### 4. Media
Embedding images, audio, video, and external content.

| File | Topic |
|------|-------|
| `images.html` | `<img>`, `alt`, `srcset`, `<figure>`, image formats, lazy loading |
| `audio-video.html` | `<audio>`, `<video>`, `<source>`, `<track>`, autoplay, poster |
| `iframe.html` | `<iframe>`, `sandbox` attribute, embedding maps and YouTube |
| `youtube-embed.html` | Embedding YouTube + external pages, `allow` vs `sandbox`, framing refusal via `X-Frame-Options` |

### 5. Tables
Structuring tabular data.

| File | Topic |
|------|-------|
| `basic-table.html` | `<table>`, `<caption>`, `<thead>`, `<tbody>`, `<tfoot>`, `<th scope>`, `<td>` |
| `spanning.html` | `colspan`, `rowspan`, combined spanning |

### 6. Forms
User input, form submission, and advanced form controls.

| File | Topic |
|------|-------|
| `inputs.html` | All `<input>` types: text, email, password, number, range, date, color, file, checkbox, radio |
| `form-structure.html` | `<form>` attributes, `<label>`, `<select>`, `<optgroup>`, `<textarea>`, `<fieldset>`, `<legend>`, buttons |
| `simple_form.html` + `show_result.html` | Form submits (GET) to a results page that reads URL params |
| `validation.html` | Constraint Validation API (`validity`, `setCustomValidity`), `:user-invalid`/`:user-valid`, live field validation, password strength meter |
| `datalist-output-meter.html` | `<datalist>` autocomplete, `<output>` for computed results, `<meter>` gauge (low/high/optimum), `<progress>` determinate and indeterminate |
| `browser_clock.html` + `validation.js` | Countdown timer with reusable input-validation helper |
| `shopping_list.html` + `validation.js` | `<datalist>` autocomplete + dynamic results table with totals |

### 7. Semantic
Meaningful document structure.

| File | Topic |
|------|-------|
| `semantic-elements.html` | `<header>`, `<nav>`, `<main>`, `<article>`, `<section>`, `<aside>`, `<footer>`, `<time>`, `<details>`, `<dialog>` |

### 8. Head & Meta
Document metadata, SEO, and social sharing.

| File | Topic |
|------|-------|
| `head-meta.html` | `charset`, `viewport`, `<title>`, `description`, Open Graph, Twitter cards, favicons, `<link rel>`, `defer` vs `async` |
| `responsive-viewport.html` | `<meta name="viewport">`, CSS `@media` queries, mobile-first design |

---

## Advanced Topics

### 9. Accessibility
Making HTML usable for everyone, including keyboard and screen-reader users.

| File | Topic |
|------|-------|
| `aria-roles.html` | ARIA roles, `aria-label`, `aria-live` live regions, accessible tab widget |
| `keyboard-focus.html` | Tab order, `tabindex`, skip links, focus rings, focus trap in modals |

### 10. Canvas
Pixel-based 2D drawing and animation via the `<canvas>` API.

| File | Topic |
|------|-------|
| `canvas-basics.html` | Shapes, paths, Bezier curves, text, gradients, shadows, transforms, pixel manipulation, paint demo |
| `canvas-animation.html` | `requestAnimationFrame`, bouncing balls, sine waves, particle system, analog clock |

### 11. SVG
Scalable vector graphics — DOM-accessible, CSS-styleable, resolution-independent.

| File | Topic |
|------|-------|
| `svg-basics.html` | `rect`, `circle`, `ellipse`, `line`, `polyline`, `polygon`, `path` commands, `defs`, gradients, filters, JS + CSS integration |
| `svg-animation.html` | CSS animations on SVG (`spin`, `pulse`, stroke draw-on), SMIL (`animate`, `animateTransform`, `animateMotion`), JS-driven animation |

### 12. Web Components
Browser-native component model — no framework required.

| File | Topic |
|------|-------|
| `template-slot.html` | `<template>` cloning, named `<slot>` for Shadow DOM content projection |
| `custom-elements.html` | `customElements.define()`, lifecycle callbacks (`connectedCallback`, `attributeChangedCallback`), `observedAttributes`, Shadow DOM — with `<progress-ring>`, `<copy-code>`, `<count-down>` demos |

### 13. Media — Advanced
Modern image loading patterns and format selection.

| File | Topic |
|------|-------|
| `picture-responsive.html` | `<picture>` art direction, `srcset` + `sizes` resolution switching, `x` density descriptors, lazy loading strategy, AVIF/WebP format selection |

### 14. Native Browser APIs
Built-in HTML-powered interactions requiring minimal JavaScript.

| File | Topic |
|------|-------|
| `drag-drop.html` | Drag events (`dragstart`, `dragover`, `drop`), `dataTransfer`, Kanban board demo, OS file drop zone |
| `dialog-popover.html` | Native `<dialog>` (modal, focus trap, `::backdrop`, `returnValue`), Popover API (`popover`, `popovertarget`, `showPopover()`), modal vs. popover comparison |
| `contenteditable.html` | `contenteditable` attribute, inline editing, mini rich-text editor with toolbar, `document.execCommand`, XSS safety notes |
| `web-storage.html` | `localStorage` / `sessionStorage` — persistent key/value storage with `JSON.stringify` for objects |

### 15. End Projects
Small, self-contained mini-projects that stitch concepts from earlier topics into something runnable.

| File | Topic |
|------|-------|
| `cool_calculator2.0.html` | Two-operand calculator (+, −) — a grid of buttons, simple state machine, Bootstrap styling |
| `todo-list.html` | Full todo app — forms, lists, checkboxes, and `localStorage` persistence |

## Usage

Open any `.html` file directly in your browser — no build step required.

For the interactive lab with a live editor + preview, open `lab.html` and pick a topic. Each step's HTML is editable and re-renders on change. Multi-file steps (like the button with external JS, or the shopping list) expose every file as a tab in the editor and auto-inline sibling `<script src>` / `<link href>` references so the sandboxed preview can run them.
