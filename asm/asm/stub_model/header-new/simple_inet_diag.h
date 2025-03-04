#ifndef __SIMPLE_INET_DIAG_H__
#define __SIMPLE_INET_DIAG_H__
enum {
	INET_DIAG_NONE,
	INET_DIAG_MEMINFO,
	INET_DIAG_INFO,
	INET_DIAG_VEGASINFO,
	INET_DIAG_CONG,
	INET_DIAG_TOS,
	INET_DIAG_TCLASS,
	INET_DIAG_SKMEMINFO,
	INET_DIAG_SHUTDOWN,
	INET_DIAG_DCTCPINFO,
	INET_DIAG_PROTOCOL,  /* response attribute only */
	INET_DIAG_SKV6ONLY,
	INET_DIAG_LOCALS,
	INET_DIAG_PEERS,
	INET_DIAG_PAD,
	INET_DIAG_MARK,
	INET_DIAG_BBRINFO,
	__INET_DIAG_MAX,
};

/* INET_DIAG_VEGASINFO */

struct tcpvegas_info {
	u32	tcpv_enabled;
	u32	tcpv_rttcnt;
	u32	tcpv_rtt;
	u32	tcpv_minrtt;
};

/* INET_DIAG_DCTCPINFO */

struct tcp_dctcp_info {
	u16	dctcp_enabled;
	u16	dctcp_ce_state;
	u32	dctcp_alpha;
	u32	dctcp_ab_ecn;
	u32	dctcp_ab_tot;
};

/* INET_DIAG_BBRINFO */

struct tcp_bbr_info {
	/* u64 bw: max-filtered BW (app throughput) estimate in Byte per sec: */
	u32	bbr_bw_lo;		/* lower 32 bits of bw */
	u32	bbr_bw_hi;		/* upper 32 bits of bw */
	u32	bbr_min_rtt;		/* min-filtered RTT in uSec */
	u32	bbr_pacing_gain;	/* pacing gain shifted left 8 bits */
	u32	bbr_cwnd_gain;		/* cwnd gain shifted left 8 bits */
};

union tcp_cc_info {
	struct tcpvegas_info	vegas;
	struct tcp_dctcp_info	dctcp;
	struct tcp_bbr_info	bbr;
};
#endif
