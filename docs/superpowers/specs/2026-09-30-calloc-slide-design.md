# calloc 부록 슬라이드 설계

## 목표

`realloc` 슬라이드 바로 뒤에 복사해 넣을 수 있는 `calloc` 학습용 부록 단일 슬라이드 PPTX를 만든다.

## 범위

- 참조 파일: `D:/jsy/Krafton Jungle/4week, 5week/week5/1팀 발표자료_정승영.pptx`
- 출력 파일은 단일 슬라이드 PPTX이며, 원본 파일은 수정하지 않는다.
- 참조한 `realloc` 슬라이드와 같은 배경, 글꼴, 코랄색 강조, 2단 레이아웃을 사용한다.
- 사용자가 원본에 복사해 넣을 것이므로 순번·목차·슬라이드 번호는 단일 슬라이드 안에서 임시 표기로 둔다.

## 슬라이드 내용

- 이름: `calloc`
- 이름 풀이: `contiguous allocation`
- 헤더: `<stdlib.h>`, `ISO C`
- 원형: `void *calloc(size_t count, size_t size);`
- 개념 표기: `할당_주소 = calloc(요소_개수, 요소_크기);`
- 하는 일: `count × size` 바이트를 할당하고 모든 바이트를 0으로 초기화한다.
- 인자: `count`는 요소 개수, `size`는 요소 하나의 바이트 크기이다.
- 반환값: 성공하면 할당 블록의 시작 포인터, 실패하면 `NULL`이다.
- 사용 예: `int **rows = calloc(ROWS, sizeof *rows);` 후 `NULL` 검사와 `perror`, `exit` 처리.
- 확인하지 않으면: `count × size` 계산이 넘칠 수 있고, `NULL` 확인 없이 사용하면 안 되며, 사용이 끝나면 `free`해야 한다.
- 과제 연결: 08번 포인터 표 초기화.

## 검증

- 출력물은 새 파일명으로 저장해 원본을 보존한다.
- 단일 슬라이드 PPTX인지 확인한다.
- 렌더링으로 새 슬라이드의 텍스트 잘림과 겹침이 없는지 확인한다.
- PowerPoint 패키지 무결성과 레이아웃 검사를 통과해야 한다.
