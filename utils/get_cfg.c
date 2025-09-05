#include "../defs.h"

int getConfigs()
{
    printMsg("Setting up router....\nReading configs from files at configs folder....\n");
    FILE *cur_file;
    int cur_line = 1;
    char line[50];

    for (int i = 0; i < R_SIZE; i++)
    {
        neighbors[i] = -1;
        routers[i].id = -1;
    }
    neighbors[routerId - 1] = 0;

    cur_file = fopen(path_els, "r");
    if (cur_file == NULL)
    {
        printMsg("Exiting... Couldn't locate %s\n", path_els);
        return 1;
    }
    while (fgets(line, sizeof(line), cur_file) != NULL)
    {
        int r1, r2, cost;
        int qtyValues = sscanf(line, "%d %d %d", &r1, &r2, &cost);
        
        if (qtyValues == 3)
        {
            if (r1 == routerId)
            {
                neighbors[r2 - 1] = cost;
            }
            else if (r2 == routerId)
            {
                neighbors[r1 - 1] = cost;
            }
            else
                printMsg("... no router %d in line %d. skipping ...\n", routerId, cur_line);
        }
        else
            printMsg("... couldn't treat line %d. skipping ...\n", cur_line);
        cur_line++;
    }
    fclose(cur_file);

    cur_file = fopen(pathRtr, "r");
    if (cur_file == NULL)
    {
        printMsg("Exiting... Couldn't locate %s\n", path_els);
        return 1;
    }

    cur_line = 1;

    while (fgets(line, sizeof(line), cur_file) != NULL)
    {
        int router, cur_port;
        char cur_ip[15];
        int qtyValues = sscanf(line, "%d %d %15s", &router, &cur_port, cur_ip);

        if (qtyValues == 3)
        {
            routers[router - 1].id = router;
            strcpy(routers[router - 1].ip, cur_ip);
            routers[router - 1].port = cur_port;
            if (router == routerId)
            {
                port = cur_port;
                strcpy(ip, cur_ip);
            }
        }
        else
            printMsg("... couldn't treat line %d. skipping ...\n", cur_line);

        cur_line++;
    }

    fclose(cur_file);

    return 0;
}
