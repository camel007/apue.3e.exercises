#include <time.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

void string_time(struct tm *tmp, char *buf, size_t size) {
    strftime(buf, size, "%Y年%m年%e日 %A %H时%M分%S秒 %Z", tmp);
}

int main() {
    printf("bytes of time_t: %ld\n", sizeof(time_t));

    time_t t = time(NULL);
    printf("current time: %ld\n", t);

    struct tm *cur_time = localtime(&t);

    char buf[1024] = {0};
    setlocale(LC_TIME, "zh_CN.UTF-8"); // 设置为中文日期编码格式
    tzset();

    system("date");
    string_time(cur_time, buf, 1024);
    printf("%s\n", buf);

    time_t largest_time_t = 0x7FFFFFFFFFFFFF; //0x7FFFFFFFFFFFFFFF
    struct tm *largest_tm = localtime(&largest_time_t);
    string_time(largest_tm, buf, 1024);
    printf("larget time: %s\n", buf);

    return 0;
}
