# C 라이브러리 자연 분류와 색상 통일 구현 계획

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 21장 PPTX의 함수 분류를 `4·5·4·3`으로 재구성하고 발표용 1~4장과 학습용 5~21장의 함수 색상을 일관되게 만든다.

**Architecture:** 기존 JavaScript 생성기의 함수 데이터와 슬라이드별 색상 설정만 수정한다. 새 분류 배열로 목차와 부록 순서를 함께 제어한 뒤 새 파일명으로 내보내고 21장을 렌더링해 확인한다.

**Tech Stack:** JavaScript ES modules, `@oai/artifact-tool`, PowerShell, Codex 프레젠테이션 검증 도구

## Global Constraints

- 전체 슬라이드는 21장이다.
- 민트 4개, 파랑 5개, 코랄 4개, 노랑 3개로 분류한다.
- 목차와 슬라이드 6~21의 순서 및 색상이 일치한다.
- 기존 남색 배경, Pretendard와 Consolas 글꼴, 레이아웃을 유지한다.

---

### Task 1: 색상 체계와 목차 수정

**Files:**
- Modify: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/build/build_c_library_2min.mjs`

**Interfaces:**
- Consumes: `COLORS`, `decoder()`, `appendixData`, `studyOrder`, `addStudyIndexSlide()`
- Produces: 새 분류와 일치하는 슬라이드 1~21

- [ ] **Step 1: 슬라이드 1의 대표 함수를 교체한다**

```text
strchr() = COLORS.mint
strcpy() = COLORS.blue
malloc() = COLORS.coral
```

- [ ] **Step 2: decoder가 함수별 색상을 받을 수 있게 한다**

`decoder()`에서 `item.color ?? accent`를 함수 이름 색상으로 사용한다. 슬라이드 2와 3의 각 항목에 최종 분류 색상을 지정한다.

- [ ] **Step 3: 슬라이드 4의 메모리 함수 색상을 통일한다**

`malloc`, `realloc`, `free`를 모두 `COLORS.coral`로 표시하고 `strchr · strtok`은 민트로 유지한다.

- [ ] **Step 4: 목차 문구와 분류 목록을 수정한다**

함수 개수 보조 문구를 삭제하고 하단 설명을 다음 문장으로 바꾼다.

```text
색이 같은 함수끼리는 하는 일과 사용할 때 조심할 점이 비슷합니다.
```

분류는 아래 목록을 사용한다.

```text
민트: strchr, strcmp, strlen, strtok
파랑: strcpy, strncpy, memcpy, memset, snprintf
코랄: malloc, realloc, free, strdup
노랑: printf, perror, exit
```

- [ ] **Step 5: 부록 순서와 snprintf 색상을 수정한다**

```text
strchr, strcmp, strlen, strtok,
strcpy, strncpy, memcpy, memset, snprintf,
malloc, realloc, free, strdup,
printf, perror, exit
```

`snprintf`의 `accent`는 `COLORS.blue`로 변경한다.

### Task 2: 새 파일 생성과 검증

**Files:**
- Create: `C:/Users/sam12/.codex/visualizations/2026/09/29/01a0eb5f-1c7a-7f93-bea8-4db16396c710/output/C_library_memory_safety_study_21slides_v2.pptx`
- Copy: `D:/jsy/Krafton Jungle/4week, 5week/week5/debugging_lab_docker/C_library_memory_safety_study_21slides_v2.pptx`

**Interfaces:**
- Consumes: Task 1의 생성기
- Produces: 검증된 21장 PPTX와 렌더링 PNG

- [ ] **Step 1: 생성기를 실행한다**

Expected: 21장 PPTX 생성, 패키지 및 레이아웃 검사 통과

- [ ] **Step 2: 21장을 모두 렌더링한다**

Expected: `slide-1.png`부터 `slide-21.png`까지 생성

- [ ] **Step 3: 모든 슬라이드를 시각적으로 확인한다**

슬라이드 1~5의 색상 일관성, 목차 가독성, 슬라이드 6~21의 순서·색상·텍스트 잘림을 확인한다.

- [ ] **Step 4: 자동 검증을 수행한다**

Expected: 슬라이드 수 21, 함수 16개 순서 일치, 레이아웃 오류 0, 폰트 정책 통과, 출력 복사본 해시 일치
