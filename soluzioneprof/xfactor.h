/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _XFACTOR_H_RPCGEN
#define _XFACTOR_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct Output {
	char *nomeGiudice;
	int punteggioTot;
};
typedef struct Output Output;

#define OPERATION 0x20000013
#define OPERATIONVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define GIUDICE_IN_TESTA 1
extern  Output * giudice_in_testa_1(void *, CLIENT *);
extern  Output * giudice_in_testa_1_svc(void *, struct svc_req *);
#define ESPRIMI_VOTO 2
extern  int * esprimi_voto_1(char **, CLIENT *);
extern  int * esprimi_voto_1_svc(char **, struct svc_req *);
extern int operation_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define GIUDICE_IN_TESTA 1
extern  Output * giudice_in_testa_1();
extern  Output * giudice_in_testa_1_svc();
#define ESPRIMI_VOTO 2
extern  int * esprimi_voto_1();
extern  int * esprimi_voto_1_svc();
extern int operation_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_Output (XDR *, Output*);

#else /* K&R C */
extern bool_t xdr_Output ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_XFACTOR_H_RPCGEN */
