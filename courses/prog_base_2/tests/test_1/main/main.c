#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "library.h"

void pf(void * listener) {
    puts("OK");
}

void pf1(void * listener) {
    puts("NO OK");
}

/*int main()
{
    OLD CODE (another): !!!!

    library_t * library = library_new();

    user_t * user1 = user_new("Ivan");
    user_t * user2 = user_new("Petro");
    user_t * user3 = user_new("Nikita");
    user_t * user4 = user_new("Oleg");

    book_t * book1 = book_new("Book1", 10);
    book_t * book2 = book_new("Book2", 5);

        //begin test subscribe
        library_subscribe(library, user1, pf);
        library_subscribe(library, user2, pf1);
        library_subscribe(library, user3, pf1);

        library_unsubscribe(library, user1, pf);

        library_doCallbak(library);
        //end test subscribe

        book_addUser(book1, user1);
        book_addUser(book1, user2);
        book_addUser(book1, user3);

        book_addUser(book2, user1);
        book_addUser(book2, user4);

        printf("First book: %i\n", book_countUsers(book1));
        printf("Second book: %i\n", book_countUsers(book2));

        library_addBook(library, book1);
        library_addBook(library, book2);
        printf("Lib books: %i\n", library_countBooks(library));

    book_free(book1);
    book_free(book2);

    user_free(user1);
    user_free(user2);
    user_free(user3);
    user_free(user4);

    library_free(library);
    return 0;
}*/

#include <stdlib.h>  // !
#include <stdarg.h>  // !
#include <stddef.h>  // !
#include <setjmp.h>  // !

#include <cmocka.h>

static void test(void **state)
{
    library_t * library = library_new();

    user_t * user = user_new("Ivan");

    book_t * book1 = book_new("Book1");
    book_t * book2 = book_new("Book2");
    book_t * book3 = book_new("Book3");
    book_t * book4 = book_new("Book4");
    book_t * book5 = book_new("Book5");

        library_addBook(library, book1);
        library_addBook(library, book2);
        library_addBook(library, book3);
        library_addBook(library, book4);
        library_addBook(library, book5);

        book_addUser(book1, user);
        book_addUser(book2, user);
        book_addUser(book3, user);
        book_addUser(book4, user);
        book_addUser(book5, user);

        list_t * list = library_getBooksTime(library, 8);

        assert_int_equal(book_getStatus(book1), 1);
        assert_int_equal(book_getStatus(NULL), -1);

        list_free(list);


        list_t * NullListTime = library_getBooksTime(library, -1);
        assert_int_equal(NullListTime, NULL);
        list_free(NullListTime);

        list_t * NullList= library_getBooksTime(NULL, 2);
        assert_int_equal(NullList, NULL);
        list_free(NullList);

    book_free(book1);
    book_free(book2);
    book_free(book3);
    book_free(book4);
    book_free(book5);

    user_free(user);

    library_free(library);
}

int main(void) {
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
