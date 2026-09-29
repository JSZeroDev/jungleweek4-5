# C Library Study Appendix Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Extend the validated four-slide C library presentation with sixteen consistent study-reference slides and export a new twenty-slide PPTX.

**Architecture:** Reuse the existing `@oai/artifact-tool` builder so the first four slides remain visually identical. Define the sixteen functions as structured data, render each with one shared appendix layout, finalize the new deck, render all pages, inspect the appendix, and copy the validated file beside the original deck.

**Tech Stack:** Bundled Node.js, `@oai/artifact-tool`, presentation finalizer, bundled Python renderer

## Global Constraints

- Keep the original first four slides and their speaker notes.
- Add exactly sixteen appendix slides, one per function, for twenty total slides.
- Retain the navy, ivory, mint, coral, Pretendard, and Consolas design system.
- Each appendix slide includes name reading, header, prototype, inputs, return value, behavior, safe example, risk, and challenge locations.
- Save to a new filename without overwriting the four-slide presentation.

---

### Task 1: Add the appendix slide system

**Files:**
- Modify: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/build/build_c_library_2min.mjs`
- Create: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/output/C_library_memory_safety_study_20slides.pptx`

**Interfaces:**
- Consumes: the approved appendix design and the existing four-slide builder
- Produces: `addAppendixSlide(slideData, index)` and a twenty-slide `Presentation`

- [ ] **Step 1: Mark one presentation edit operation**

Run `mark_artifact_operation_started.mjs` with `--operation-kind edit --expected-output-count 1 --output-format pptx`.

- [ ] **Step 2: Add sixteen complete function records**

Each record must define `name`, `reading`, `header`, `standard`, `prototype`, `purpose`, `inputs`, `returns`, `code`, `risk`, and `challenges` for `strchr`, `strcmp`, `strlen`, `strcpy`, `strncpy`, `memcpy`, `memset`, `strtok`, `malloc`, `realloc`, `free`, `printf`, `snprintf`, `perror`, `exit`, and `strdup`.

- [ ] **Step 3: Add one reusable appendix layout**

Use a flat two-column design: explanation and signature on the left, code and coral risk statement on the right. Keep title text at least 32pt, body text at least 18pt, and code at least 19pt.

- [ ] **Step 4: Export and finalize revision**

Finalize with `explicitTotalSlideCount: 20`, no required tables or charts, and the existing Pretendard and Consolas font policy.

Expected: package integrity, geometry, font, and first-party import checks pass with twenty slides.

### Task 2: Render, inspect, and deliver

**Files:**
- Create: `D:/jsy/Krafton Jungle/4week, 5week/week5/debugging_lab_docker/C_library_memory_safety_study_20slides.pptx`

**Interfaces:**
- Consumes: the finalized twenty-slide output
- Produces: a hash-identical delivered PPTX and twenty rendered PNGs

- [ ] **Step 1: Render every final slide**

Run `render_slides.py` with the bundled runtime and verify that exactly twenty PNG files are produced.

- [ ] **Step 2: Inspect the appendix**

Inspect all sixteen appendix slides at readable size. Repair clipping, overlap, unreadable text, or inconsistent spacing in the builder and regenerate under a new output revision if necessary.

- [ ] **Step 3: Verify requirements**

Confirm twenty slides, four preserved notes, sixteen distinct appendix titles, zero layout findings, and successful first-party import.

- [ ] **Step 4: Copy the validated file unchanged**

Copy the final PPTX beside the original four-slide file and compare SHA-256 hashes.
