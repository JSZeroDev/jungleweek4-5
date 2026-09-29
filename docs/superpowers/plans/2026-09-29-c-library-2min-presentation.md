# C Library Two-Minute Presentation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Create a polished, editable four-slide PPTX that explains C library memory-safety checks within a two-minute presentation.

**Architecture:** A single JavaScript ES module uses `@oai/artifact-tool` to build the slides, code examples, native diagrams, and Korean speaker notes. The deck is exported to a private workspace, finalized with the presentation validators, rendered to PNG, visually inspected, then copied unchanged beside the debugging lab.

**Tech Stack:** Bundled Node.js, `@oai/artifact-tool`, presentation finalizer, bundled Python renderer

## Global Constraints

- Use exactly four 16:9 slides.
- Target a spoken duration of 1 minute 45 seconds to 1 minute 50 seconds.
- Explain representative functions aloud and leave the remaining abbreviations as visual reference.
- Use a navy background, ivory text, mint and coral accents, large typography, and editable native slide objects.
- Keep slide text concise and put the full Korean script in speaker notes.
- Do not misstate `strchr`, `strncpy`, `snprintf`, or `realloc` behavior.

---

### Task 1: Author the presentation

**Files:**
- Create: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/build/build_c_library_2min.mjs`
- Create: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/build/candidate.pptx`

**Interfaces:**
- Consumes: the approved design at `D:/jsy/Krafton Jungle/4week, 5week/docs/superpowers/specs/2026-09-29-c-library-2min-presentation-design.md`
- Produces: an in-memory `Presentation` and a four-slide draft PPTX

- [ ] **Step 1: Mark the artifact operation**

Run from the presentation skill directory:

```powershell
& 'C:\Users\sam12\.cache\codex-runtimes\codex-primary-runtime\dependencies\node\bin\node.exe' container_tools/mark_artifact_operation_started.mjs --operation-kind create --expected-output-count 1 --output-format pptx
```

Expected: successful artifact-operation marker with one PPTX output.

- [ ] **Step 2: Write the presentation builder**

Implement these exact slide responsibilities in `build_c_library_2min.mjs`:

```text
1. C 라이브러리 함수와 메모리 안전: scope and central message
2. 반환된 주소의 유효성: strchr code and NULL branch
3. 메모리 접근 범위: hello plus null byte and strcpy overflow
4. 메모리 수명: malloc/realloc/free timeline and conclusion
```

Use the selected Korean sans-serif font for prose and a verified monospaced font for code. Add notes timed to 15, 30, 30, and 35 seconds.

- [ ] **Step 3: Export the draft**

Run the module with bundled Node.js and linked bundled packages.

Expected: `candidate.pptx` and one PNG preview per slide.

### Task 2: Finalize and inspect the deck

**Files:**
- Create: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/output/C_library_memory_safety_2min.pptx`
- Create: `D:/jsy/Krafton Jungle/4week, 5week/week5/debugging_lab_docker/C_library_memory_safety_2min.pptx`

**Interfaces:**
- Consumes: the four-slide presentation from Task 1
- Produces: validated final PPTX and rendered slide images

- [ ] **Step 1: Run presentation finalization**

Declare these requirements:

```js
{
  explicitTotalSlideCount: 4,
  requiredNativeTableOwnerSlides: [],
  requiredNativeChartOwnerSlides: []
}
```

Expected: package integrity, slide geometry, font policy, and Artifact Tool re-import checks pass.

- [ ] **Step 2: Render all four final slides**

Use the bundled rendering command from the installed presentation skill.

Expected: four PNG images at 16:9 without missing text or broken fonts.

- [ ] **Step 3: Inspect each rendered slide**

Check every full-size PNG for clipping, overlap, unreadable text, excessive density, inconsistent spacing, and weak visual hierarchy. If an issue appears, edit the builder and finalize to a new revision filename.

- [ ] **Step 4: Verify content and notes**

Confirm the deck has exactly four slides, the representative examples are correct, every abbreviation has a short meaning, and the combined script stays under two minutes at a normal Korean speaking pace.

- [ ] **Step 5: Copy the validated file unchanged**

```powershell
Copy-Item -LiteralPath 'C:\Users\sam12\.codex\visualizations\2026\09\29\01a0eb5f-1c7a-7f93-bea8-4db16396c710\output\C_library_memory_safety_2min.pptx' -Destination 'D:\jsy\Krafton Jungle\4week, 5week\week5\debugging_lab_docker\C_library_memory_safety_2min.pptx'
```

Expected: destination SHA-256 matches the validated output.
