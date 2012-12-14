#include <citrusleaf/citrusleaf.h>
#include <citrusleaf/udf.h>
#include <as_hashmap.h>
#include <as_buffer.h>
#include <as_msgpack.h>
#include <stdio.h>


#define HOST "127.0.0.1"
#define PORT 3000
#define TIMEOUT 100

#define LOG(msg, ...) \
    { printf("%s:%d - ", __FILE__, __LINE__); printf(msg, ##__VA_ARGS__ ); printf("\n"); }


int main(int argc, char ** argv) {
    
    if ( argc != 2 ) {
        LOG("invalid arguments.");
        return 1;
    }

    char *          filename    = argv[1];
    cl_cluster *    cluster     = NULL;
    char *          error       = NULL;
    int             rc          = 0;

    citrusleaf_init();

    cluster = citrusleaf_cluster_create();
    citrusleaf_cluster_add_host(cluster, HOST, PORT, TIMEOUT);
    
    rc = citrusleaf_udf_remove(cluster, filename, &error);
    
    if ( rc ) {
        printf("error: %s\n", error);
        free(error);
        error = NULL;
    }
    
    return rc;
}
