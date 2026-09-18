# Jungle Week 4–5

하나의 Git 저장소에서 주차별 학습 파일을 관리하며, 각 프로젝트는 별도 Dev Container를 사용합니다.

```text
week4/
  Data-Structures/          # 제공된 자료구조 예제
  data_structures_docker/   # 자료구조 실습 환경과 기존 풀이
week5/
  debugging_lab_docker/     # 메모리 디버깅 실습 환경
```

## VS Code에서 컨테이너 열기

1. Docker Desktop을 실행합니다.
2. week4는 `week4/data_structures_docker`를, week5는 `week5/debugging_lab_docker`를 각각 별도 VS Code 창으로 엽니다.
3. 각 창에서 **Dev Containers: Reopen in Container**를 실행합니다.
4. 기존 컨테이너를 사용 중이었다면 **Dev Containers: Rebuild and Reopen in Container**를 실행해 변경된 마운트 설정을 적용합니다.

각 컨테이너는 자체 Dockerfile을 사용합니다. 저장소 전체는 `/workspaces/jungleweek4-5`에 연결되고, 시작 작업 폴더는 해당 주차의 프로젝트입니다. week4에서 제공 예제는 `../Data-Structures`, 기존 풀이는 `./Data-Structures`에 있습니다.

두 컨테이너는 같은 호스트 파일과 Git 저장소를 공유합니다. 파일 편집은 즉시 반영되며, 브랜치 전환·커밋 작업은 한 창에서 진행하세요. 컨테이너에 Git이 없으면 호스트 터미널에서 Git 명령을 실행할 수 있습니다.

## 커밋 기록

기존 main의 커밋 기록을 유지한 채 폴더 정리 커밋을 추가했습니다. 기존 master와 `recovery/main-before-force-20260918` 브랜치도 보존합니다. 하위 프로젝트는 서브모듈이 아닌 일반 파일로 관리합니다.
