#include <zephyr.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <logging/log.h>
#include <zenoh-pico.h>

#define LOG_MODULE_NAME app
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

void data_handler(const zn_sample_t *sample, const void *arg)
{
    (void)arg;

    LOG_INF(">> [Subscription listener] Received msg" );
}

void main(void)
{
    LOG_INF( "Starting Openthread with config:" );
    LOG_INF( "Network Name: %s", log_strdup(CONFIG_OPENTHREAD_NETWORK_NAME) );
    LOG_INF( "Channel: %d", CONFIG_OPENTHREAD_CHANNEL );
    LOG_INF( "PANID: %d", CONFIG_OPENTHREAD_PANID );
    LOG_INF( "XPANID: %s", log_strdup(CONFIG_OPENTHREAD_XPANID) );
    LOG_INF( "Network Key: %s", log_strdup(CONFIG_OPENTHREAD_NETWORKKEY) );

    sleep( 5 );

    char *zenoh_uri = "/demo/example/**";
    zn_properties_t *config = zn_config_default();
    zn_properties_insert(config, ZN_CONFIG_PEER_KEY, z_string_make( CONFIG_ZENOH_ROUTER_LOCATOR ) );

    zn_session_t *s = NULL;
    while( s == NULL )
    {
        LOG_INF( "Connecting to zenohd at: %s", log_strdup( CONFIG_ZENOH_ROUTER_LOCATOR ) );
        s = zn_open(config);

        if (s == 0)
        {
            LOG_INF("Unable to open zenoh session!");
            sleep( 3 );
            continue;
        }

        LOG_INF( "Connected!" );
    }
    
    // Start the read session session lease loops
    int rez = znp_start_read_task(s);
    if( rez == 0 )
    {
        LOG_INF( "Started read task" );
    }
    else{
        LOG_ERR( "Failed read task %d", rez );
    }
    znp_start_lease_task(s);

    zn_subscriber_t *sub = zn_declare_subscriber(s, zn_rname( zenoh_uri ), zn_subinfo_default(), data_handler, NULL );
    if (sub == 0)
    {
        LOG_ERR("Unable to declare subscriber.");
        
    }

    LOG_INF("Awaiting data"); 
    while( true )
    {
        sleep( 1 );
    }

    zn_undeclare_subscriber(sub);
    zn_close(s);

    return;    
}