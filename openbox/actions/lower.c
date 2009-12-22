#include "openbox/actions.h"
#include "openbox/stacking.h"
#include "openbox/window.h"

typedef struct {
    gboolean app;
} Options;

static gpointer setup_func(xmlNodePtr node);
static gboolean run_func(ObActionsData *data, gpointer options);

void action_lower_startup(void)
{
    actions_register("Lower", setup_func, NULL, run_func);
}

static gpointer setup_func(xmlNodePtr node)
{
    xmlNodePtr n;
    Options *o;

    o = g_new0(Options, 1);

    if ((n = obt_xml_find_node(node, "app")))
        o->app = obt_xml_node_bool(n);
    return o;
}

/* Always return FALSE because its not interactive */
static gboolean run_func(ObActionsData *data, gpointer options)
{
    Options *o = options;

    if (data->client) {
        actions_client_move(data, TRUE);
        if (o->app)
            stacking_lower_app(data->client);
        else
            stacking_lower(CLIENT_AS_WINDOW(data->client));
        actions_client_move(data, FALSE);
    }

    return FALSE;
}
