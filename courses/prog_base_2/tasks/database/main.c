#include <stdio.h>
#include <stdlib.h>

#include "db_manager.h"
#include "ScrumMaster.h"

int main(void) {
    const char * dbFile = "ScrumMaster.db";
    db_t * db = db_new(dbFile);

    master_t masterList[10];

    for (int i = 1; i < db_countScrumMaster(db) + 1; i++)
    {
        master_t * sm = db_getScrumMasterById(db, i);
        masterList_set(&masterList[i - 1], sm);
    }
    //master_printList(masterList, db_countScrumMaster(db));

    printf("Number of Scrum Masters: %i\n\n", db_countScrumMaster(db));

    db_deleteScrumMaster(db, 3);
    puts("Deleted");

    printf("Number of Scrum Masters: %i\n\n", db_countScrumMaster(db));

    //master_printList(masterList, db_countScrumMaster(db));

    master_set(&masterList[db_countScrumMaster(db)], "Tom", "Abramson", 2, 3, "1997-10-12", 5.0);
    printf("Added a new Scrum Master, his ID: %i\n", db_insertScrumMaster(db, &masterList[db_countScrumMaster(db)]));

    printf("Number of Scrum Masters: %i\n\n", db_countScrumMaster(db));

    //master_printList(masterList, db_countScrumMaster(db));

    master_t * master = malloc(sizeof(struct ScrumMaster));
    master_set(master, "Ivan", "Burlaka", 4, 2, "1950-01-02", 3.7);
    masterList_set(&masterList[1], master);
    db_updateScrumMaster(db, master, 2);
    puts("Updated:");
    master_printList(masterList, db_countScrumMaster(db));

    master = db_getScrumMasterById(db, 3);
    puts("You chose this Scrum Master:");
    master_print(master);

    int count = db_getScrumMasterTask(db, 3, 6, masterList, 100);
    puts("Filtered data:");
    master_printList(masterList, count);

    db_free(db);
    return 0;
}
