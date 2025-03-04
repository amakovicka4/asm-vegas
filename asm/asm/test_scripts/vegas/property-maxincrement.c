/**
 * TCP Vegas Original Algorithm Verification
 * 
 * This file checks the correctness of the original implementaton of TCP Vegas
 * so that it can be checked to the aggregate algorithm version. 
 * 
 */

#ifndef script_property
#define script_property
#include "../../stub_model/header-new/share.h"
#include "/home/asm/asm/CA_variants/tcp_vegas.c"

extern struct tcp_congestion_ops tcp_vegas;

u32 __VERIFIER_assert(char *msg, int cond)
{
	char printmsg[1024];
	if (cond){
		sprintf (printmsg, "\x1B[32m%s passed! \x1B[0m\n", msg);
		important_msg(printmsg);
		return 0;
	} else {
		sprintf (printmsg, "\x1B[31m%s violated!\x1B[0m\n", msg);
		important_msg(printmsg);
		return 1;
	}
}

void __VERIFIER_nondet_u32(u32 *variable, char *name, u32 min_value, u32 max_value) 
{
#ifdef KLEE
	klee_make_symbolic (variable, sizeof(u32), name);
	klee_assume ((*variable) >= min_value);
	if (klee_is_symbolic(min_value))
		printf("[Symbolic value] %-25s : min=some symbolic variable\n", name);
	else
		printf("[Symbolic value] %-25s : min=%u\n", name, min_value);
	klee_assume ((*variable) <= max_value);
	if (klee_is_symbolic(max_value))
		printf("[Symbolic value] %-25s : max=some symbolic variable\n", name);
	else
		printf("[Symbolic value] %-25s : max=%u\n", name, max_value);
#else
	(*variable) = max_value;
	printf("[Concrete value] %s = %u\n", name, max_value);
#endif
}

void copy_tcp(struct tcp_sock *tpa, struct vegas *caa, struct tcp_sock *tpb, struct vegas *cab)
{
	tpb->snd_cwnd = tpa->snd_cwnd;
	tpb->snd_ssthresh = tpa->snd_ssthresh;
	tpb->snd_cwnd_cnt = tpa->snd_cwnd_cnt;

    cab->baseRTT = caa->baseRTT;
    cab->beg_snd_cwnd = caa->beg_snd_cwnd;
    cab->beg_snd_una = caa->beg_snd_una;
    cab->beg_snd_nxt = caa->beg_snd_nxt;
    cab->doing_vegas_now = caa->doing_vegas_now;
    cab->cntRTT = caa->cntRTT;
    cab->minRTT = caa->minRTT;

}

void print_tcp(char *msg, struct tcp_sock *tp, struct vegas *ca){
    return;
	//printf("%s: target %u, cwnd %u, K %u, origin %u, last_max %u, snd_cwnd_cnt %u, cnt %u, last_cwnd %u, last_time %u, tcp_cwnd %u, ack_cnt %u\n", msg,
	//	ca->bic_target, tp->snd_cwnd, ca->bic_K, ca->bic_origin_point, ca->last_max_cwnd, tp->snd_cwnd_cnt, ca->cnt, ca->last_cwnd, ca->last_time, ca->tcp_cwnd, ca->ack_cnt);
}


int main(int argc, char* argv[]){

///////// Parameter initilization ///////////////////////

    u32 MIN_SSTHRESH;
    u32 MAX_SSTHRESH;

    u32 MIN_CWND_CNT;
    u32 MAX_CWND_CNT;       

    u32 MIN_CWND;
    u32 MAX_CWND;

    // TODO - Initialize min/max values from command line

    tcp_vegas_register();

///////// TCP initilization ///////////////////////
	struct tcp_sock tcp_sock_struct; 
	struct sock *sk = (struct sock *)&tcp_sock_struct;
	struct tcp_sock *tp = &tcp_sock_struct;
	struct inet_connection_sock *icsk = inet_csk(sk);
    struct vegas *ca = inet_csk_ca(sk);

    tcp_vegas_init(sk);

    memset(&tcp_sock_struct, 0, sizeof(struct tcp_sock));
	tcp_set_congestion_control(sk, &tcp_vegas); 
	struct net net_namespace;
	memset(&net_namespace, 0, sizeof(struct net));
	tp->inet_conn.icsk_inet.sk.sk_net.net = &net_namespace;
	tcp_sk_init(&net_namespace);
	tcp_init_sock(sk);
	if (icsk->icsk_ca_ops->init)
		icsk->icsk_ca_ops->init(sk);
	tcp_ca_event(sk, CA_EVENT_TX_START);

///////// Symbolic Variable Initilization ///////////////////////
    u32 sym_cwnd;    
    u32 sym_snd_ssthresh;      
    u32 sym_cwnd_cnt;          

	__VERIFIER_nondet_u32(&sym_cwnd, "cwnd", MIN_CWND, MAX_CWND);
	__VERIFIER_nondet_u32(&sym_snd_ssthresh, "ssthresh", MIN_SSTHRESH, MAX_SSTHRESH);
	__VERIFIER_nondet_u32(&sym_cwnd_cnt, "cwnd_cnt", 0, sym_cwnd-1); 


    tp->snd_cwnd = 10;
    tp->snd_ssthresh = 1;
    tp->snd_cwnd_cnt = 0;


    

    ///////// Verify Property /////////////////////////////
	u32 cwnd_init = tp->snd_cwnd;
    for(int i=0;i<cwnd_init;i++){

        tcp_vegas_cong_avoid(sk,0,1);

}

    printf("snd_cwnd = %u, snd_ssthresh = %u, snd_cwnd_cnt = %u base_rtt = %u", tp->snd_cwnd,
    tp->snd_ssthresh,tp->snd_cwnd_cnt, ca->baseRTT);

    return 0;
}

#endif