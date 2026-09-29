# C 라이브러리 색상 목차 및 재정렬 구현 계획

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 기존 발표용 4장을 보존하면서 색상 목차 1장과 색상별로 정렬된 함수 학습 슬라이드 16장을 포함하는 21장 PPTX를 만든다.

**Architecture:** 기존 JavaScript 프레젠테이션 생성기의 함수 데이터 배열을 색상 분류 순서로 재배치하고, 발표 슬라이드와 함수 슬라이드 사이에 목차 생성 함수를 호출한다. 같은 생성기에서 PPTX를 다시 내보내고 렌더링·구조·레이아웃 검사를 수행한다.

**Tech Stack:** JavaScript ES modules, `@oai/artifact-tool`, PowerShell, Codex 프레젠테이션 검증 도구

## Global Constraints

- 슬라이드 1~4는 기존 렌더링과 동일해야 한다.
- 전체 슬라이드는 21장이다.
- 목차와 함수 슬라이드는 민트, 파랑, 코랄, 노랑 순서다.
- 각 분류에 함수가 정확히 네 개씩 들어간다.
- 기존 Pretendard, Consolas, 남색 배경 디자인을 유지한다.

---

### Task 1: 목차 및 함수 순서 구현

**Files:**
- Modify: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/build/build_c_library_2min.mjs`

**Interfaces:**
- Consumes: 기존 `deck`, `slide()`, `text()`, `line()`, `COLORS`, `functionSlides`
- Produces: `addStudyIndexSlide()`와 색상별로 정렬된 `functionSlides`

- [ ] **Step 1: 현재 함수 순서를 확인한다**

Run: `rg -n "name: \"(strchr|strcmp|strlen|strtok|strcpy|strncpy|memcpy|memset|malloc|realloc|free|strdup|printf|snprintf|perror|exit)\"" build/build_c_library_2min.mjs`

Expected: `strtok`과 `strdup`이 각각의 색상 묶음 끝에 있지 않은 현재 순서가 출력된다.

- [ ] **Step 2: 목차 생성 함수를 추가한다**

목차 제목은 `학습 자료 목차`, 부제는 `색상으로 구분한 16개 C 라이브러리 함수`로 작성한다. 네 분류와 함수는 아래 데이터를 사용한다.

```js
const studyGroups = [
  { color: COLORS.mint, label: "문자열 탐색·비교·분리", names: "strchr · strcmp · strlen · strtok" },
  { color: COLORS.blue, label: "문자열·메모리 복사와 초기화", names: "strcpy · strncpy · memcpy · memset" },
  { color: COLORS.coral, label: "동적 메모리와 수명 관리", names: "malloc · realloc · free · strdup" },
  { color: COLORS.yellow, label: "출력·오류·프로그램 종료", names: "printf · snprintf · perror · exit" },
];
```

- [ ] **Step 3: 함수 데이터 배열을 목차 순서로 재배치한다**

정확한 순서는 다음과 같다.

```text
strchr, strcmp, strlen, strtok,
strcpy, strncpy, memcpy, memset,
malloc, realloc, free, strdup,
printf, snprintf, perror, exit
```

- [ ] **Step 4: 목차를 슬라이드 5로 삽입하고 페이지 번호를 6부터 시작한다**

```js
addStudyIndexSlide();
functionSlides.forEach((data, index) => addFunctionSlide(data, index + 6));
```

- [ ] **Step 5: 생성기를 실행한다**

Run: bundled Node.js로 `build/build_c_library_2min.mjs` 실행

Expected: `output/C_library_memory_safety_study_21slides.pptx` 생성, 종료 코드 0

### Task 2: 렌더링 및 검증

**Files:**
- Create: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/output/C_library_memory_safety_study_21slides.pptx`
- Copy: `D:/jsy/Krafton Jungle/4week, 5week/week5/debugging_lab_docker/C_library_memory_safety_study_21slides.pptx`

**Interfaces:**
- Consumes: Task 1의 생성기 출력
- Produces: 렌더링 PNG 21개와 최종 검증 영수증

- [ ] **Step 1: 21장을 PNG로 렌더링한다**

Expected: `slide-1.png`부터 `slide-21.png`까지 생성된다.

- [ ] **Step 2: 시각 검사를 수행한다**

목차의 네 분류가 서로 구분되고 함수 이름이 읽히는지, 함수 슬라이드에 잘림이나 겹침이 없는지 확인한다.

- [ ] **Step 3: 구조와 레이아웃 검사를 수행한다**

Expected: 슬라이드 수 21, 패키지 오류 0, 레이아웃 오류 0, 폰트 정책 통과

- [ ] **Step 4: 순서와 기존 발표 슬라이드 보존을 검증한다**

Expected: 함수 순서가 목차와 일치하고, 슬라이드 1~4의 PNG SHA-256이 기존 20장 버전과 동일하다.

- [ ] **Step 5: 최종 파일을 사용자 폴더로 복사한다**

Expected: 원본과 복사본의 SHA-256이 동일하다.
