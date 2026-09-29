# C Library Slide Accuracy Audit Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Correct the factual issues in the 21-slide C library deck while preserving slides 3, 4, and 5 exactly.

**Architecture:** Apply copy-only changes in the existing JavaScript presentation builder, regenerate the complete deck through the presentation finalizer, and compare the regenerated output with the prior deck. Use extracted slide text, rendered images, package/layout validation, and image hashes for slides 3–5 as independent checks.

**Tech Stack:** JavaScript ESM, `@oai/artifact-tool`, bundled Node.js/Python runtimes, PowerPoint `.pptx`, Poppler rendering utilities, PowerShell.

## Global Constraints

- The deck remains exactly 21 slides.
- Slides 3, 4, and 5—including speaker notes—must not change.
- Function order and category colors must remain unchanged.
- Slide 1 says `C 표준·POSIX 라이브러리 함수` because `strdup` is POSIX.
- Slide 2 contains `strchr`, `malloc`, `realloc`, `strtok`, and `strdup`, with no `strcmp`.
- Slide 7 describes `strcmp` as comparing bytes as `unsigned char` values.
- Slide 16 states the valid `realloc` input and post-success pointer-lifetime rule.
- Slide 21 explains that code after `exit` does not execute and that library-level `exit` removes the caller's recovery/cleanup opportunity.

---

### Task 1: Update the Presentation Source

**Files:**
- Modify: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/build/build_c_library_2min.mjs`

**Interfaces:**
- Consumes: the approved accuracy-audit design and the existing 21-slide builder.
- Produces: a builder whose visible copy and speaker notes match the approved corrections without changing slide count, order, or category colors.

- [ ] **Step 1: Capture the baseline for protected slides**

Run:

```powershell
Get-FileHash -Algorithm SHA256 'C:\Users\sam12\.codex\visualizations\2026\09\29\01a0eb5f-1c7a-7f93-bea8-4db16396c710\build\slide-3.png','C:\Users\sam12\.codex\visualizations\2026\09\29\01a0eb5f-1c7a-7f93-bea8-4db16396c710\build\slide-4.png','C:\Users\sam12\.codex\visualizations\2026\09\29\01a0eb5f-1c7a-7f93-bea8-4db16396c710\build\slide-5.png'
```

Expected: three SHA-256 hashes are recorded before regeneration.

- [ ] **Step 2: Apply the approved copy corrections**

Edit the builder so that:

```text
Slide 1 label: C 표준·POSIX 라이브러리 함수
Slide 1 note: C 문법의 내장 함수가 아니라 C 표준 및 POSIX 라이브러리 함수
Slide 2 title: 포인터 반환값과 NULL
Slide 2 decoder: strchr, malloc, realloc, strtok, strdup
Slide 2 note: strchr=찾지 못함, strtok=다음 토큰 없음, malloc/realloc/strdup=할당 실패
strcmp purpose: 각 바이트를 unsigned char 값 기준으로 앞에서부터 비교한다.
realloc input: ptr is an allocation start address or NULL
realloc purpose/return/risk: ptr==NULL behaves like malloc; failure preserves the old block; success ends the old block lifetime and invalidates old aliases/interior pointers; avoid new_size==0 in this learning material
exit risk: exit 이후 코드는 실행되지 않으며 라이브러리 함수에서 호출하면 호출자가 복구·정리할 기회를 잃는다.
```

- [ ] **Step 3: Verify the source contains every required correction**

Run:

```powershell
rg -n "C 표준·POSIX|포인터 반환값과 NULL|strdup|unsigned char|ptr == NULL|new_size == 0|호출자가 오류를 복구" 'C:\Users\sam12\.codex\visualizations\2026\09\29\01a0eb5f-1c7a-7f93-bea8-4db16396c710\build\build_c_library_2min.mjs'
```

Expected: each approved phrase appears, and the slide 2 decoder block contains no `strcmp`.

### Task 2: Regenerate and Validate the Deck

**Files:**
- Generate: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/output/C_library_memory_safety_study_21slides_v2.pptx`
- Generate: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/.codex-finalizer/C_library_memory_safety_study_21slides_v2.validation.json`

**Interfaces:**
- Consumes: the corrected builder from Task 1.
- Produces: a validated 21-slide PowerPoint and updated slide previews/layout exports.

- [ ] **Step 1: Run the builder with the bundled Node.js runtime**

Run:

```powershell
$env:NODE_PATH='C:\Users\sam12\.cache\codex-runtimes\codex-primary-runtime\dependencies\node\node_modules'
& 'C:\Users\sam12\.cache\codex-runtimes\codex-primary-runtime\dependencies\node\bin\node.exe' 'C:\Users\sam12\.codex\visualizations\2026\09\29\01a0eb5f-1c7a-7f93-bea8-4db16396c710\build\build_c_library_2min.mjs'
```

Expected: exit code 0 and a finalized `.pptx` with 21 slides.

- [ ] **Step 2: Check protected-slide image hashes**

Run the same `Get-FileHash` command from Task 1 Step 1.

Expected: slide 3, 4, and 5 hashes exactly match the recorded baseline hashes.

- [ ] **Step 3: Inspect validation results**

Run:

```powershell
Get-Content -Raw 'C:\Users\sam12\.codex\visualizations\2026\09\29\01a0eb5f-1c7a-7f93-bea8-4db16396c710\.codex-finalizer\C_library_memory_safety_study_21slides_v2.validation.json'
```

Expected: package integrity, layout geometry, fonts, and slide-count checks report success with no blocking errors.

- [ ] **Step 4: Render and inspect the corrected slides**

Render all slides using the presentation skill's bundled render utility, then inspect slides 1, 2, 7, 16, and 21 as images.

Expected: no clipped text, overlaps, unintended color changes, or layout regressions.

### Task 3: Deliver the Corrected PowerPoint

**Files:**
- Copy to: `D:/jsy/Krafton Jungle/4week, 5week/week5/debugging_lab_docker/C_library_memory_safety_study_21slides_v2.pptx`

**Interfaces:**
- Consumes: the validated final deck from Task 2.
- Produces: the user-facing PowerPoint in the course project directory.

- [ ] **Step 1: Copy the validated deck to the course directory**

Run:

```powershell
Copy-Item -LiteralPath 'C:\Users\sam12\.codex\visualizations\2026\09\29\01a0eb5f-1c7a-7f93-bea8-4db16396c710\output\C_library_memory_safety_study_21slides_v2.pptx' -Destination 'D:\jsy\Krafton Jungle\4week, 5week\week5\debugging_lab_docker\C_library_memory_safety_study_21slides_v2.pptx' -Force
```

Expected: the destination exists and has the same SHA-256 hash as the validated source.

- [ ] **Step 2: Open the corrected deck for the user**

Use the Codex file-opening tool on the destination `.pptx`.

Expected: the corrected PowerPoint opens in the app for review.

- [ ] **Step 3: Report the exact correction set and verification evidence**

Report that slides 1, 2, 7, 16, and 21 changed; slides 3, 4, and 5 were hash-identical; and all presentation validation checks passed.
