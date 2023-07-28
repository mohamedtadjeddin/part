#include <stdio.h>
#include <stdlib.h>

// a struct for parts
typedef struct
{
    int count;      // The number of parts
    int price;      // the price of each part
    int extra_part; // The additional part that comes when purchasing
} Part;

// a struct for components
typedef struct
{
    int known;        // Is the component known to the repair crew(=0 -> broken ,=1 -> known ,=2 -> fixed)
    int part_req;     // The part required to fix
    int num_comp_rev; // Number of components revealed when fixed
    int *comp_rev;    // Array of revealed components when fixed
} Component;

// a struct for nodes which we will be using in the queue
typedef struct
{
    int component;
    struct node *next;
} node;

// a function to add a component to the queue
void add_to_queue(node *components_list, int component)
{
    node *helper = components_list;
    // we move to the end of the queue
    while (helper->next != NULL)
    {
        helper = helper->next;
    }
    // we add the new component in the end of the queue
    node *new = malloc(sizeof(node));
    new->component = component;
    new->next = NULL;
    helper->next = new;
}

// a function to remove a component from the queue(the first one in the queue)
int remove_from_queue(node *components_list)
{
    node *helper = components_list->next;
    // If the queue is not empty, we delete the first component in the queue and we return that component
    if (helper != NULL)
    {
        components_list->next = helper->next;
        return helper->component;
    }
    // If the queue is empty we return -1
    return -1;
}

int main()
{
    int P;               //(P is uppercase) The number of parts that can be used to repair the ship
    int c;               // The cost of ordering the part corresponding
    int e;               // The extra part that will be received
    int C;               // The number of components that need to be repaired
    int p;               // (P is lowercase)
    int n;               // The number of broken components revealed upon repairing the component
    int total_price = 0; // The total price to fix the ship
    // The head of the queue
    node *components_list = malloc(sizeof(node));
    components_list->next = NULL;
    // Taking the number of parts that can be used to repair the ship
    scanf("%d", &P);
    // We create an array of parts
    Part parts[P];
    // for each part we take two inputs(the price and the extra part)
    for (int i = 0; i < P; i++)
    {
        scanf("%d %d", &c, &e);
        parts[i].price = c;
        parts[i].extra_part = e;
        // We initialize the count of each part to 0
        parts[i].count = 0;
    }
    // Taking the number of components that need to be repaired
    scanf("%d", &C);
    // We create an array of components
    Component components[C];
    /*For each component we take an input
    ( part requested and The number of broken components revealed upon repairing the component and
    the components revealed )*/
    for (int i = 0; i < C; i++)
    {
        char input[C - 1];
        components[i].known = 0;
        scanf("%d %[^\n]", &p, input);

        components[i].part_req = p;
        sscanf(input, "%d", &n);
        components[i].num_comp_rev = n;
        components[i].comp_rev = malloc(n * sizeof(int));

        for (int j = 0; j < n; j++)
        {
            sscanf(input + (2 * j) + 2, "%d", &components[i].comp_rev[j]);
        }
    }
    // A variable will help as to determine if we fixed all the components or not(-1 means everything is fixed)
    int indicator;
    int removed;
    do
    {
        indicator = -1;
        // Adding to the queue the components with status known(=1) if there isn't, we add the first broken component(status =0)
        for (int i = 0; i < C; i++)
        {
            if (components[i].known == 1)
            {
                add_to_queue(components_list, i);
                indicator = -2;
            }
            // saving the index of the first broken component
            if (components[i].known == 0 && indicator != -2 && indicator < 0)
            {
                indicator = i;
            }
        }
        // If everything is fixed(indicator=-1) we are done
        if (indicator == -1)
        {
            break;
        }
        /* If the isn't a component with staus=1(known) we set the first broken component status to 1
        (indicator will be the index of the first broken part if != -1 && != -2)*/
        if (indicator != -1 && indicator != -2)
        {
            components[indicator].known = 1;
        }
        /*Handling the queue*/
        // While the components list(queue)is not NULL(not empty), we handle components inside it
        while (components_list->next != NULL)
        {
            // We remove the first component in the list and we store that component in "removed"
            removed = remove_from_queue(components_list);
            // If removed = -1 , it means the queue is empty
            if (removed == -1)
            {
                components_list->next = NULL;
            }
            // If the queue is not empty
            else
            {
                // If the part required to fix the current component is available
                if (parts[components[removed].part_req - 1].count > 0)
                {
                    // We decrease the count of that part by 1
                    parts[components[removed].part_req - 1].count--;
                    // We set the status of the component in the array of components to 2 (fixed)
                    components[removed].known = 2;
                    // We add to the queue the revealed components to 1(known)(if there are not already fixed)
                    for (int j = 0; j < components[removed].num_comp_rev; j++)
                    {
                        if (components[components[removed].comp_rev[j] - 1].known != 2)
                        {
                            add_to_queue(components_list, components[removed].comp_rev[j] - 1);
                            components[components[removed].comp_rev[j] - 1].known = 2;
                        }
                    }
                }
                // If there are not available parts to fix the current component , we buy the part needed
                else
                {
                    // We add the price of the part to the total price
                    total_price = total_price + parts[components[removed].part_req - 1].price;
                    // We increase the count of that part by 1
                    parts[components[removed].part_req - 1].count++;
                    // We increase the count of the extra part
                    parts[parts[components[removed].part_req - 1].extra_part - 1].count++;
                    // We add the current component ton the end of the queue
                    add_to_queue(components_list, removed);
                }
            }
        }
    } while (indicator != -1);
    // After fixing all the components, we display the total price
    printf("\n%d\n", total_price);
    return 0;
}