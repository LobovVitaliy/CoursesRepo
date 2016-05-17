#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "text.h"

int vowel(char * str) {
    char vowel[12] = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u', 'Y', 'y'};

    for(int i = 0; i < 12; i++)
    {
        if(str[0] == vowel[i])
        {
            return 1;
        }
    }
    return 0;
}

int overflow(char * str) {
    if(strlen(str) > 20)
        return 1;
    else
        return 0;
}

void double_f(text_t * self, char * newSent) {
    printf("Double string: %s\n", newSent);
    test_setStatusD(self, 1);
}

void overflow_f(text_t * self, char * newSent) {
    printf("Overflow!!! Last string: %s\n", newSent);
}

int main()
{
    char buffer[512];

    text_t * text = text_new();

    test_subsDouble(text, double_f);
    test_subsOverflow(text, overflow_f);

    text_subscribe(text, vowel);
    text_subscribe(text, overflow);

    do
    {
        printf("Writer: ");
        gets(buffer);
        text_push(text, buffer);
    }
    while (text_getSize(text) != 10);

    text_printf(text);

    text_free(text);

    return 0;
}


/*#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

static void text_new__void__size_zero (void **state)
{
    text_t * text = text_new();
        assert_int_equal(text_getSize(text), 0);
    text_free(text);
}

static void text_push__text__pushText (void **state)
{
    text_t * text = text_new();
        text_push(text, "OK");
        assert_int_equal(text_getSize(text), 1);
    text_free(text);
}

static void text_pop__text__popText (void **state)
{
    text_t * text = text_new();
        text_push(text, "OK");
        assert_string_equal(text_pop(text), "OK");
    text_free(text);
}

static void text_getEl__text_Index__text (void **state)
{
    text_t * text = text_new();
        text_push(text, "OK0");
        text_push(text, "OK1");
        text_push(text, "OK2");
        assert_string_equal(text_getEl(text, 1), "OK1");
    text_free(text);
}

static void text_subscribe__text_callback__pushCallback (void **state)
{
    text_t * text = text_new();
        text_subscribe(text, vowel);
        assert_int_equal(text_listGetSize(text), 1);
    text_free(text);
}

static void callback_double__text_string__statusTrue (void **state)
{
    text_t * text = text_new();
        test_subsDouble(text, double_f);
        text_push(text, "OK");
        text_push(text, "OK");
        assert_int_equal(test_getStatusD(text), 1);
    text_free(text);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(text_new__void__size_zero),
        cmocka_unit_test(text_push__text__pushText),
        cmocka_unit_test(text_pop__text__popText),
        cmocka_unit_test(text_getEl__text_Index__text),
        cmocka_unit_test(text_subscribe__text_callback__pushCallback),
        cmocka_unit_test(callback_double__text_string__statusTrue)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}*/
