#include "./protocol.h"
#include "../../header/stdhead.h"

/*
    这里提供的函数支持把 body 和 struct之间互相转换
*/
// 负责把body -> struct
int transformProtocolBody(ProtocolBody &body , CMD cmd , void *data);
// 协议体转换
int TransformUserRegister(ProtocolBody &body , struct CMD_USER_REGISTER_BODY &userregister);
int TransformUserRegisterResp(ProtocolBody &body , struct CMD_USER_REGISTER_RESP_BODY &userregisterresp);
int TransformUserLogin(ProtocolBody &body , struct CMD_USER_LOGIN_BODY &userlogin);
int TransformUserLoginResp(ProtocolBody &body , struct CMD_USER_LOGIN_RESP_BODY &userloginresp);
int TransformUserLogout(ProtocolBody &body , struct CMD_USER_LOGOUT_BODY &userlogout);
int TransformUserLogoutResp(ProtocolBody &body , struct CMD_USER_LOGOUT_RESP_BODY &userlogoutresp);
int TransformDevLogin(ProtocolBody &body , struct CMD_DEV_LOGIN_BODY &devlogin);
int TransformDevLoginResp(ProtocolBody &body , struct CMD_DEV_LOGIN_RESP_BODY &devloginresp);
int TransformDevLogout(ProtocolBody &body , struct CMD_DEV_LOGOUT_BODY &devlogout);
int TransformDevLogoutResp(ProtocolBody &body , struct CMD_DEV_LOGOUT_RESP_BODY &devlogoutresp);
int TransformHeart(ProtocolBody &body , struct CMD_HEART_BODY &heart);
int TransformHeartResp(ProtocolBody &body , struct CMD_HEART_RESP_BODY &heartresp);
int TransformMsg(ProtocolBody &body , struct CMD_MSG_BODY &msg);
int TransformMsgResp(ProtocolBody &body , struct CMD_MSG_RESP_BODY &msgresp);
int TransformNotice(ProtocolBody &body , struct CMD_NOTICE_BODY &notice);
int TransformNoticeResp(ProtocolBody &body , struct CMD_NOTICE_RESP_BODY &noticeresp);
int TransformUserAddDev(ProtocolBody &body , struct CMD_USER_ADD_DEV_BODY &useradddev);
int TransformUserAddDevResp(ProtocolBody &body , struct CMD_USER_ADD_DEV_RESP_BODY &useradddevresp);
int TransformUserDelDev(ProtocolBody &body , struct CMD_USER_DEL_DEV_BODY &userdeldev);
int TransformUserDelDevResp(ProtocolBody &body , struct CMD_USER_DEL_DEV_RESP_BODY &userdeldevresp);
int TransformGetList(ProtocolBody &body , struct CMD_GETLIST_BODY &getlist);
int TransformGetListResp(ProtocolBody &body , struct CMD_GETLIST_RESP_BODY &getlistresp);
int TransformGetStatus(ProtocolBody &body , struct CMD_GETSTATUS_BODY &getstatus);
int TransformGetStatusResp(ProtocolBody &body , struct CMD_GETSTATUS_RESP_BODY &getstatusresp);
int TransformEcho(ProtocolBody &body , struct CMD_ECHO_BODY &echo);
int TransformEchoResp(ProtocolBody &body , struct CMD_ECHO_RESP_BODY &echoresp);


// struct -> body
int packProtocolBody(ProtocolBody &body , CMD cmd , void *data);
// 协议体打包
int PakUserRegister(ProtocolBody &body , struct CMD_USER_REGISTER_BODY &userregister);
int PakUserRegisterResp(ProtocolBody &body , struct CMD_USER_REGISTER_RESP_BODY &userregisterresp);
int PackUserLogin(ProtocolBody &body , struct CMD_USER_LOGIN_BODY &userlogin);
int PackUserLoginResp(ProtocolBody &body , struct CMD_USER_LOGIN_RESP_BODY &userloginresp);
int PackUserLogout(ProtocolBody &body , struct CMD_USER_LOGOUT_BODY &userlogout);
int PackUserLogoutResp(ProtocolBody &body , struct CMD_USER_LOGOUT_RESP_BODY &userlogoutresp);
int PackDevLogin(ProtocolBody &body , struct CMD_DEV_LOGIN_BODY &devlogin);
int PackDevLoginResp(ProtocolBody &body , struct CMD_DEV_LOGIN_RESP_BODY &devloginresp);
int PackDevLogout(ProtocolBody &body , struct CMD_DEV_LOGOUT_BODY &devlogout);
int PackDevLogoutResp(ProtocolBody &body , struct CMD_DEV_LOGOUT_RESP_BODY &devlogoutresp);
int PackHeart(ProtocolBody &body , struct CMD_HEART_BODY &heart);
int PackHeartResp(ProtocolBody &body , struct CMD_HEART_RESP_BODY &heartresp);
int PackMsg(ProtocolBody &body , struct CMD_MSG_BODY &msg);
int PackMsgResp(ProtocolBody &body , struct CMD_MSG_RESP_BODY &msgresp);
int PackNotice(ProtocolBody &body , struct CMD_NOTICE_BODY &notice);
int PackNoticeResp(ProtocolBody &body , struct CMD_NOTICE_RESP_BODY &noticeresp);
int PackUserAddDev(ProtocolBody &body , struct CMD_USER_ADD_DEV_BODY &useradddev);
int PackUserAddDevResp(ProtocolBody &body , struct CMD_USER_ADD_DEV_RESP_BODY &useradddevresp);
int PackUserDelDev(ProtocolBody &body , struct CMD_USER_DEL_DEV_BODY &userdeldev);
int PackUserDelDevResp(ProtocolBody &body , struct CMD_USER_DEL_DEV_RESP_BODY &userdeldevresp);
int PackGetList(ProtocolBody &body , struct CMD_GETLIST_BODY &getlist);
int PackGetListResp(ProtocolBody &body , struct CMD_GETLIST_RESP_BODY &getlistresp);
int PackGetStatus(ProtocolBody &body , struct CMD_GETSTATUS_BODY &getstatus);
int PackGetStatusResp(ProtocolBody &body , struct CMD_GETSTATUS_RESP_BODY &getstatusresp);
int PackEcho(ProtocolBody &body , struct CMD_ECHO_BODY &echo);
int PackEchoResp(ProtocolBody &body , struct CMD_ECHO_RESP_BODY &echoresp);