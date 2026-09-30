# calloc Standalone Slide Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Create one editable `calloc` PowerPoint slide matching the team's `realloc` reference slide.

**Architecture:** Build a new 16:9 one-slide deck with native editable text boxes and rounded rectangles. Mirror the reference slide's dark navy background, Pretendard/Consolas typography, coral dynamic-memory accent, and two-column layout; validate the new file before delivery.

**Tech Stack:** JavaScript ESM, `@oai/artifact-tool`, bundled Node.js/Python runtimes, PowerPoint `.pptx`.

## Global Constraints

- Create a standalone one-slide PPTX; do not modify the team deck.
- Match the `realloc` slide layout, colors, and font pairing.
- Use `calloc(size_t count, size_t size)` and the approved Korean learning copy.
- Save the output under a new filename in `week5`.
- Validate slide count, package integrity, layout, fonts, and rendered text fit.

---

### Task 1: Build and Validate the Standalone Slide

**Files:**
- Create: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/build/build_calloc_standalone.mjs`
- Create: `D:/jsy/Krafton Jungle/4week, 5week/week5/calloc_슬라이드_삽입용.pptx`

**Interfaces:**
- Consumes: the approved content and rendered `realloc` reference.
- Produces: one editable PowerPoint slide that can be copied into the team deck.

- [ ] **Step 1: Mark the presentation creation operation and author the slide**

Run the presentation creation marker, then create the one-slide deck with `calloc` function details, a `calloc` allocation example, and its allocation/NULL/free safety rules.

- [ ] **Step 2: Export and validate the deck**

Run the builder through `finalizePresentation` with expected slide count `1`, package integrity, layout geometry, Pretendard/Consolas font policy, and first-party import checks.

- [ ] **Step 3: Render and inspect the slide**

Render the finalized deck to PNG and inspect the full slide at readable size.

- [ ] **Step 4: Copy the validated deck to the course folder and verify its hash**

Copy the validated PPTX unchanged to `D:/jsy/Krafton Jungle/4week, 5week/week5/calloc_슬라이드_삽입용.pptx`, then compare SHA-256 hashes.
