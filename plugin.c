#include <nfp/mem_atomic.h>

#include <pif_plugin.h>

//#include <pkt_ops.h>

#include <pif_headers.h>

#include <nfp_override.h>

#include <pif_common.h>

#include <std/hash.h>

#include <nfp/me.h>

#include <nfp.h>

#include <stdlib.h>

#include <stdint.h>

#define BUCKET_SIZE 7

__shared __export __addr40 __emem uint32_t i;
static uint8_t first = 1;
int pif_plugin_lookup_state(EXTRACTED_HEADERS_T *headers, MATCH_DATA_T *match_data) {
    __xrw uint32_t randval ;
    __xrw uint64_t time;
    //time = me_tsc_read();
    if (first) {
        first = 0;
        local_csr_write(local_csr_pseudo_random_number,(local_csr_read(local_csr_timestamp_low) & 0xffff) + 1);
        //srand(time);
    }
    randval = local_csr_read(local_csr_pseudo_random_number)  ;
    //randval = rand() % 10;
//    pif_plugin_meta_set__rand_meta__random_num(headers,randval);
    mem_write_atomic(&randval, &i, sizeof(randval));
    return PIF_PLUGIN_RETURN_FORWARD;
    return PIF_PLUGIN_RETURN_FORWARD;
}

