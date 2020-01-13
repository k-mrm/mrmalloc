#include <stdio.h>
#include <limits.h>

#include "malloc.h"

typedef struct Person Person;

struct Person {
    char *name;
    int age;
    enum { MAN, WOMAN, OTHER } sex;
};

Person *new_person(char *name, int age, int sex) {
    Person *new = mrmalloc(sizeof(Person));

    new->name = name;
    new->age = age;
    new->sex = sex;

    return new;
}

void dump_person(Person *p) {
    printf("%s, %d, %s\n",
           p->name,
           p->age,
           (p->sex == MAN) ? "man"
           : (p->sex == WOMAN) ? "woman"
           : "other");
}

int main(void) {
    printf("%zdbyte\n", __alignof__(mem_header));
    printf("%zdbyte\n", sizeof(mem_header));

    /*
    Person *garin = new_person("garin", 3141, OTHER);
    dump_person(garin);
    mrfree(garin); */

    for(;;) {
        void *a = mrmalloc(200000);
        mrfree(a);
    }

    return 0;
}
