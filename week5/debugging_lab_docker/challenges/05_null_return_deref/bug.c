/*
 * Challenge 05 — NULL 반환 미확인 역참조 (심화: 설정 템플릿 확장기)
 *
 * [시나리오]
 *   key=value 설정 저장소(Config)와, "${key}" 자리표시자를 실제 값으로 치환하는
 *   템플릿 확장기 expand() 를 만든다. 예: "http://${host}:${port}/${path}".
 *
 * [기대 동작]
 *   템플릿의 모든 ${key} 를 설정값으로 치환한 최종 문자열을 출력.
 *
 * [증상]
 *   cfg_get() 은 키가 없으면 NULL 을 돌려준다. expand() 는 이 반환값을 검사하지 않고
 *   곧장 strlen()/memcpy() 에 넘긴다. 템플릿에 설정에 없는 키(${path})가 섞여 있으면
 *   그 순간 v==NULL 이 되어 strlen(NULL) 에서 SIGSEGV.
 *   크래시는 strlen(libc) 안에서 나지만, 원인은 "검사 없이 흘려보낸 NULL 반환값"이다.
 *
 * [gdb 로 잡기]
 *   make gdb NAME=05_null_return_deref
 *   (gdb) run                     → 크래시(SIGSEGV)
 *   (gdb) bt                      → strlen ← expand ← main
 *   (gdb) frame 1 ; print key      → 어떤 키를 찾다가 죽었는지(예: "path")
 *   (gdb) print v                  → v == 0x0 (cfg_get 이 NULL 을 돌려줬음)
 *   (gdb) break expand             → 각 ${key} 마다 cfg_get 결과를 살펴 NULL 을 잡기
 *
 * [printf(로그)로 잡기]
 *   치환 직전 키와 조회 결과 포인터를 함께 찍는다:
 *     fprintf(stderr, "expand key=%s v=%p\n", key, (void*)v);
 *   → v 가 (nil) 로 찍힌 키가 원인.
 *   (stdout 은 버퍼링되니 stderr 로 찍어야 크래시 직전 로그가 남는다)
 *
 * TODO: cfg_get() 의 NULL 반환을 반드시 검사하라. 없는 키는 기본값("")으로 대체하거나
 *       명시적 오류로 처리한다("사용 전에 검사" 원칙).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KV 16
typedef struct {
    const char *keys[MAX_KV];
    const char *vals[MAX_KV];
    int n;
} Config;

static void cfg_set(Config *c, const char *k, const char *v) {
    if (c->n < MAX_KV) { c->keys[c->n] = k; c->vals[c->n] = v; c->n++; }
}

static const char *cfg_get(const Config *c, const char *k) {
    for (int i = 0; i < c->n; i++)
    // strcmp 함수 특징
    //strcmp(const char *s1, const char *s2) (String Compare)
        // 역할: 두 문자열의 내용을 앞에서부터 널 문자('\0')를 만날 때까지 아스키(ASCII) 값으로 비교합니다.
        // 반환값:
            // 0: 두 문자열의 내용이 완전히 일치함
            // 양수: s1이 사전순으로 뒤에 있음
            // 음수: s1이 사전순으로 앞에 있음
        if (strcmp(c->keys[i], k) == 0) return c->vals[i];
    return NULL;                       /* 없는 키 → NULL */
}

static void expand(const Config *c, const char *tmpl, char *out, size_t outcap) {
    size_t o = 0;
    for (const char *p = tmpl; *p; ) {
        if (p[0] == '$' && p[1] == '{') {
            // strchr 함수 특징
            //strchr(const char *s, int c) (String Character)는 문자열 s에서 특정 문자 c가 처음으로 등장하는 위치를 찾는 <string.h> 함수입니다.
                // 1. 기본 동작 및 반환값
                    // 동작: s가 가리키는 주소부터 널 문자('\0')까지 순차 탐색하며 문자 c를 찾습니다.
                    // 반환값:
                    // 문자를 찾은 경우: 해당 문자가 위치한 메모리 주소(포인터) 반환
                    // 문자를 찾지 못한 경우: NULL 반환
                    // 특징: 검색 대상 문자로 '\0'을 전달하면 문자열 끝의 널 종단 문자 포인터를 반환합니다.
            const char *end = strchr(p, '}');
            if (!end) break;
            char key[32];
            size_t kl = (size_t)(end - (p + 2));
            if (kl >= sizeof key) kl = sizeof key - 1;
            //memcpy 함수 특징
            //memcpy(void *dest, const void *src, size_t n) (Memory Copy)
                // 역할: src가 가리키는 메모리 주소에서부터 정확히 n바이트만큼을 dest 주소로 복사합니다.
                // 특징: 문자열뿐만 아니라 구조체, 바이너리 등 모든 데이터를 지정한 바이트 수만큼 복사합니다. 문자열 끝을 알리는 '\0'을 자동으로 붙여주지 않으므로 수동으로 널 문자를 넣어주어야 합니다.
                memcpy(key, p + 2, kl);
            key[kl] = '\0';

            const char *v = cfg_get(c, key);  
            // strlen 함수 특징
            //strlen(const char *s) (String Length)
            // 역할: 넘겨받은 메모리 주소부터 시작해 첫 번째 널 문자('\0')가 나올 때까지 바이트 수를 세어 문자열 길이를 반환합니다.
            // 주의점 (크래시 원인): 인자로 유효한 메모리 주소가 와야 합니다. NULL(0번지)을 넘기면 CPU가 접근 불가능한 주소를 읽으려 하므로 SIGSEGV(세그멘테이션 오류)가 발생하며 프로그램이 즉시 강제 종료됩니다.
            if( v != NULL){
            size_t vl = strlen(v);                 
            if (o + vl < outcap) { memcpy(out + o, v, vl); o += vl; }
            }
            p = end + 1;
        } else {
            if (o + 1 < outcap) out[o++] = *p;
            p++;
        }
    }
    out[o] = '\0';
}

int main(void) {
    /* [Thinking Point]
     * "{ .n = 0 }" 은 멤버 이름을 콕 집어 초기화하는 '지정 초기화자(designated initializer)'다.
     *   tip 1. 초기화자에 하나라도 값을 주면, 명시하지 않은 나머지 멤버는 전부 0 으로
     *          채워진다. 즉 keys[], vals[] 배열도 모두 NULL 로 초기화된다.
     *   tip 2. 만약 그냥 "Config cfg;" 로만 뒀다면 지역 변수라 n·keys·vals 가 쓰레기 값이다.
     *   생각해보기: n 이 쓰레기 값이면 cfg_set/cfg_get 에서 무슨 일이 벌어질까?
     *               */
    Config cfg = { .n = 0 };
    cfg_set(&cfg, "host", "example.com");
    cfg_set(&cfg, "port", "8080");
    // 이렇게도 풀 수 있겠으나 근본적인 해결책은 되지 않음, 다른 예시가 들어올 경우 여전히 에러가 발생하게 됨
    // cfg_set(&cfg, "path", "123abc");

    /* [Thinking Point]
     * "${host}" 처럼 ${...} 로 감싼 부분은 expand 함수가 설정값으로 치환하는 'placeholder' 다.
     *   tip 1. 이 문자열 자체는 그냥 상수 텍스트일 뿐, 컴파일러가 ${...} 를 해석하지 않는다.
     *          실제 치환은 런타임에 expand 함수 안에서 키를 찾아 값을 끼워넣는 방식으로 일어난다.
     *   tip 2. cfg_get("path") 는 등록되지 않은 키라 NULL 을 돌려준다.
     *   생각해보기: 설정에 없는 키(${path})를 만나면 expand() 는 어떤 값을 받게 되고,
     *               그 값을 검사 없이 strlen/복사에 쓰면 무슨 일이 벌어질까?
     *               (힌트: "값이 없다"는 NULL 이지 빈 문자열 ""이 아니다) */
    const char *tmpl = "http://${host}:${port}/${path}/index.html";
    char out[256];

    expand(&cfg, tmpl, out, sizeof out);   /* ${path} 치환 시 NULL 역참조 → 크래시 */

    printf("url = %s\n", out);
    return 0;
}
