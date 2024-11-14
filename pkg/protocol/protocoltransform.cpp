#include "./protocol.h"
#include "../../header/stdhead.h"

// transform 的实现
int TransformUserRegister(ProtocolBody &body, struct CMD_USER_REGISTER_BODY &userregister) {
    memcpy(userregister.name, body.data[0], body.lenParts[0]);
    memcpy(userregister.pwd, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformUserRegisterResp(ProtocolBody &body, struct CMD_USER_REGISTER_RESP_BODY &userregisterresp) {
    userregisterresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(userregisterresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformUserLogin(ProtocolBody &body, struct CMD_USER_LOGIN_BODY &userlogin) {
    memcpy(userlogin.name, body.data[0], body.lenParts[0]);
    memcpy(userlogin.pwd, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformUserLoginResp(ProtocolBody &body, struct CMD_USER_LOGIN_RESP_BODY &userloginresp) {
    userloginresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(userloginresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformUserLogout(ProtocolBody &body, struct CMD_USER_LOGOUT_BODY &userlogout) {
    memcpy(userlogout.name, body.data[0], body.lenParts[0]);
    return 0;
}
int TransformUserLogoutResp(ProtocolBody &body, struct CMD_USER_LOGOUT_RESP_BODY &userlogoutresp) {
    userlogoutresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(userlogoutresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformDevLogin(ProtocolBody &body, struct CMD_DEV_LOGIN_BODY &devlogin) {
    memcpy(devlogin.name, body.data[0], body.lenParts[0]);
    memcpy(devlogin.pwd, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformDevLoginResp(ProtocolBody &body, struct CMD_DEV_LOGIN_RESP_BODY &devloginresp) {
    devloginresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(devloginresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformDevLogout(ProtocolBody &body, struct CMD_DEV_LOGOUT_BODY &devlogout) {
    memcpy(devlogout.name, body.data[0], body.lenParts[0]);
    return 0;
}
int TransformDevLogoutResp(ProtocolBody &body, struct CMD_DEV_LOGOUT_RESP_BODY &devlogoutresp) {
    devlogoutresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(devlogoutresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}

int TransformHeart(ProtocolBody &body, struct CMD_HEART_BODY &heart) {
    return 0;
}
int TransformHeartResp(ProtocolBody &body, struct CMD_HEART_RESP_BODY &heartresp) {
    return 0;
}
int TransformMsg(ProtocolBody &body, struct CMD_MSG_BODY &msg) {
    memcpy(msg.name, body.data[0], body.lenParts[0]);
    memcpy(msg.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformMsgResp(ProtocolBody &body, struct CMD_MSG_RESP_BODY &msgresp) {
    msgresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(msgresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformNotice(ProtocolBody &body, struct CMD_NOTICE_BODY &notice) {
    memcpy(notice.msg, body.data[0], body.lenParts[0]);
    return 0;
}
int TransformNoticeResp(ProtocolBody &body, struct CMD_NOTICE_RESP_BODY &noticeresp) {
    noticeresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(noticeresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformUserAddDev(ProtocolBody &body, struct CMD_USER_ADD_DEV_BODY &useradddev) {
    memcpy(useradddev.devname, body.data[0], body.lenParts[0]);
    return 0;
}
int TransformUserAddDevResp(ProtocolBody &body, struct CMD_USER_ADD_DEV_RESP_BODY &useradddevresp) {
    useradddevresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(useradddevresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformUserDelDev(ProtocolBody &body, struct CMD_USER_DEL_DEV_BODY &userdeldev) {
    memcpy(userdeldev.devname, body.data[0], body.lenParts[0]);
    return 0;
}
int TransformUserDelDevResp(ProtocolBody &body, struct CMD_USER_DEL_DEV_RESP_BODY &userdeldevresp) {
    userdeldevresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(userdeldevresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}
int TransformGetList(ProtocolBody &body, struct CMD_GETLIST_BODY &getlist) {
    return 0;
}
int TransformGetListResp(ProtocolBody &body, struct CMD_GETLIST_RESP_BODY &getlistresp) {
    getlistresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    getlistresp.num = *(int*)body.data[1];
    for(int i = 0; i < getlistresp.num; i++){
        memcpy(getlistresp.devname[i], body.data[2 + i], body.lenParts[2 + i]);
    }
    return 0;
}
int TransformGetStatus(ProtocolBody &body, struct CMD_GETSTATUS_BODY &getstatus) {
    return 0;
}
int TransformGetStatusResp(ProtocolBody &body, struct CMD_GETSTATUS_RESP_BODY &getstatusresp) {
    getstatusresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    getstatusresp.num = *(int*)body.data[1];
    for(int i = 0; i < getstatusresp.num; i++){
        memcpy(getstatusresp.devname[i], body.data[2 + i], body.lenParts[2 + i]);
    }
    return 0;
}
int TransformEcho(ProtocolBody &body, struct CMD_ECHO_BODY &echo) {
    memcpy(echo.devname, body.data[0], body.lenParts[0]);
    memcpy(echo.msg, body.data[1],body.lenParts[1]);
    return 0;
}
int TransformEchoResp(ProtocolBody &body, struct CMD_ECHO_RESP_BODY &echoresp) {
    echoresp.cmdstatus = *(CMD_STATUS*)body.data[0];
    memcpy(echoresp.msg, body.data[1], body.lenParts[1]);
    return 0;
}

// pack 的实现
int PackUserRegister(ProtocolBody &body, struct CMD_USER_REGISTER_BODY &userregister) {
    body.numParts = 2;
    body.lenParts[0] = strlen(userregister.name);
    body.lenParts[1] = strlen(userregister.pwd);
    memcpy(body.data[0], userregister.name, body.lenParts[0]);
    memcpy(body.data[1], userregister.pwd, body.lenParts[1]);
    return 0;
}
int PackUserRegisterResp(ProtocolBody &body, struct CMD_USER_REGISTER_RESP_BODY &userregisterresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(userregisterresp.msg);
    memcpy(body.data[0], &userregisterresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], userregisterresp.msg, body.lenParts[1]);
    return 0;
}
int PackUserLogin(ProtocolBody &body, struct CMD_USER_LOGIN_BODY &userlogin) {
    body.numParts = 2;
    body.lenParts[0] = strlen(userlogin.name);
    body.lenParts[1] = strlen(userlogin.pwd);
    memcpy(body.data[0], userlogin.name, body.lenParts[0]);
    memcpy(body.data[1], userlogin.pwd, body.lenParts[1]);
    return 0;
}
int PackUserLoginResp(ProtocolBody &body, struct CMD_USER_LOGIN_RESP_BODY &userloginresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(userloginresp.msg);
    memcpy(body.data[0], &userloginresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], userloginresp.msg, body.lenParts[1]);
    return 0;
}
int PackUserLogout(ProtocolBody &body, struct CMD_USER_LOGOUT_BODY &userlogout) {
    body.numParts = 1;
    body.lenParts[0] = strlen(userlogout.name);
    memcpy(body.data[0], userlogout.name, body.lenParts[0]);
    return 0;
}
int PackUserLogoutResp(ProtocolBody &body, struct CMD_USER_LOGOUT_RESP_BODY &userlogoutresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(userlogoutresp.msg);
    memcpy(body.data[0], &userlogoutresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], userlogoutresp.msg, body.lenParts[1]);
    return 0;
}
int PackDevLogin(ProtocolBody &body, struct CMD_DEV_LOGIN_BODY &devlogin) {
    body.numParts = 2;
    body.lenParts[0] = strlen(devlogin.name);
    body.lenParts[1] = strlen(devlogin.pwd);
    memcpy(body.data[0], devlogin.name, body.lenParts[0]);
    memcpy(body.data[1], devlogin.pwd, body.lenParts[1]);
    return 0;
}
int PackDevLoginResp(ProtocolBody &body, struct CMD_DEV_LOGIN_RESP_BODY &devloginresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(devloginresp.msg);
    memcpy(body.data[0], &devloginresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], devloginresp.msg, body.lenParts[1]);
    return 0;
}
int PackDevLogout(ProtocolBody &body, struct CMD_DEV_LOGOUT_BODY &devlogout) {
    body.numParts = 1;
    body.lenParts[0] = strlen(devlogout.name);
    memcpy(body.data[0], devlogout.name, body.lenParts[0]);
    return 0;
}
int PackDevLogoutResp(ProtocolBody &body, struct CMD_DEV_LOGOUT_RESP_BODY &devlogoutresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(devlogoutresp.msg);
    memcpy(body.data[0], &devlogoutresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], devlogoutresp.msg, body.lenParts[1]);
    return 0;
}
int PackHeart(ProtocolBody &body, struct CMD_HEART_BODY &heart) {
    body.numParts = 0;
    return 0;
}
int PackHeartResp(ProtocolBody &body, struct CMD_HEART_RESP_BODY &heartresp) {
    body.numParts = 0;
    return 0;
}
int PackMsg(ProtocolBody &body, struct CMD_MSG_BODY &msg) {
    body.numParts = 2;
    body.lenParts[0] = strlen(msg.name);
    body.lenParts[1] = strlen(msg.msg);
    memcpy(body.data[0], msg.name, body.lenParts[0]);
    memcpy(body.data[1], msg.msg, body.lenParts[1]);
    return 0;
}
int PackMsgResp(ProtocolBody &body, struct CMD_MSG_RESP_BODY &msgresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(msgresp.msg);
    memcpy(body.data[0], &msgresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], msgresp.msg, body.lenParts[1]);
    return 0;
}
int PackNotice(ProtocolBody &body, struct CMD_NOTICE_BODY &notice) {
    body.numParts = 1;
    body.lenParts[0] = strlen(notice.msg);
    memcpy(body.data[0], notice.msg, body.lenParts[0]);
    return 0;
}
int PackNoticeResp(ProtocolBody &body, struct CMD_NOTICE_RESP_BODY &noticeresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(noticeresp.msg);
    memcpy(body.data[0], &noticeresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], noticeresp.msg, body.lenParts[1]);
    return 0;
}
int PackUserAddDev(ProtocolBody &body, struct CMD_USER_ADD_DEV_BODY &useradddev) {
    body.numParts = 1;
    body.lenParts[0] = strlen(useradddev.devname);
    memcpy(body.data[0], useradddev.devname, body.lenParts[0]);
    return 0;
}
int PackUserAddDevResp(ProtocolBody &body, struct CMD_USER_ADD_DEV_RESP_BODY &useradddevresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(useradddevresp.msg);
    memcpy(body.data[0], &useradddevresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], useradddevresp.msg, body.lenParts[1]);
    return 0;
}
int PackUserDelDev(ProtocolBody &body, struct CMD_USER_DEL_DEV_BODY &userdeldev) {
    body.numParts = 1;
    body.lenParts[0] = strlen(userdeldev.devname);
    memcpy(body.data[0], userdeldev.devname, body.lenParts[0]);
    return 0;
}
int PackUserDelDevResp(ProtocolBody &body, struct CMD_USER_DEL_DEV_RESP_BODY &userdeldevresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(userdeldevresp.msg);
    memcpy(body.data[0], &userdeldevresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], userdeldevresp.msg, body.lenParts[1]);
    return 0;
}
int PackGetList(ProtocolBody &body, struct CMD_GETLIST_BODY &getlist) {
    body.numParts = 0;
    return 0;
}
int PackGetListResp(ProtocolBody &body, struct CMD_GETLIST_RESP_BODY &getlistresp) {
    body.numParts = 2 + getlistresp.num;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = sizeof(int);
    memcpy(body.data[0], &getlistresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], &getlistresp.num, body.lenParts[1]);
    for(int i = 0; i < getlistresp.num; i++){
        body.lenParts[2 + i] = strlen(getlistresp.devname[i]);
        memcpy(body.data[2 + i], getlistresp.devname[i], body.lenParts[2 + i]);
    }
    return 0;
}
int PackGetStatus(ProtocolBody &body, struct CMD_GETSTATUS_BODY &getstatus) {
    body.numParts = 0;
    return 0;
}
int PackGetStatusResp(ProtocolBody &body, struct CMD_GETSTATUS_RESP_BODY &getstatusresp) {
    body.numParts = 2 + getstatusresp.num;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = sizeof(int);
    memcpy(body.data[0], &getstatusresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], &getstatusresp.num, body.lenParts[1]);
    for(int i = 0; i < getstatusresp.num; i++){
        body.lenParts[2 + i] = strlen(getstatusresp.devname[i]);
        memcpy(body.data[2 + i], getstatusresp.devname[i], body.lenParts[2 + i]);
    }
    return 0;
}
int PackEcho(ProtocolBody &body, struct CMD_ECHO_BODY &echo) {
    body.numParts = 2;
    body.lenParts[0] = strlen(echo.devname);
    body.lenParts[1] = strlen(echo.msg);
    memcpy(body.data[0], echo.devname, body.lenParts[0]);
    memcpy(body.data[1], echo.msg, body.lenParts[1]);
    return 0;
}
int PackEchoResp(ProtocolBody &body, struct CMD_ECHO_RESP_BODY &echoresp) {
    body.numParts = 2;
    body.lenParts[0] = sizeof(CMD_STATUS);
    body.lenParts[1] = strlen(echoresp.msg);
    memcpy(body.data[0], &echoresp.cmdstatus, body.lenParts[0]);
    memcpy(body.data[1], echoresp.msg, body.lenParts[1]);
    return 0;
}

int transformProtocolBody(ProtocolBody &body , CMD cmd , void *data){
    switch (cmd) {
        case CMD_USER_REGISTER:
            return TransformUserRegister(body, *(CMD_USER_REGISTER_BODY*)data);
            break;
        case CMD_USER_REGISTER_RESP:
            return TransformUserRegisterResp(body, *(CMD_USER_REGISTER_RESP_BODY*)data);
            break;
        case CMD_USER_LOGIN:
            return TransformUserLogin(body, *(CMD_USER_LOGIN_BODY*)data);
            break;
        case CMD_USER_LOGIN_RESP:
            return TransformUserLoginResp(body, *(CMD_USER_LOGIN_RESP_BODY*)data);
            break;
        case CMD_USER_LOGOUT:
            return TransformUserLogout(body, *(CMD_USER_LOGOUT_BODY*)data);
            break;
        case CMD_USER_LOGOUT_RESP:
            return TransformUserLogoutResp(body, *(CMD_USER_LOGOUT_RESP_BODY*)data);
            break;
        case CMD_DEV_LOGIN:
            return TransformDevLogin(body, *(CMD_DEV_LOGIN_BODY*)data);
            break;
        case CMD_DEV_LOGIN_RESP:
            return TransformDevLoginResp(body, *(CMD_DEV_LOGIN_RESP_BODY*)data);
            break;
        case CMD_DEV_LOGOUT:
            return TransformDevLogout(body, *(CMD_DEV_LOGOUT_BODY*)data);
            break;
        case CMD_DEV_LOGOUT_RESP:
            return TransformDevLogoutResp(body, *(CMD_DEV_LOGOUT_RESP_BODY*)data);
            break;
        case CMD_HEART:
            return TransformHeart(body, *(CMD_HEART_BODY*)data);
            break;
        case CMD_HEART_RESP:
            return TransformHeartResp(body, *(CMD_HEART_RESP_BODY*)data);
            break;
        case CMD_MSG:
            return TransformMsg(body, *(CMD_MSG_BODY*)data);
            break;
        case CMD_MSG_RESP:
            return TransformMsgResp(body, *(CMD_MSG_RESP_BODY*)data);
            break;
        case CMD_NOTICE:
            return TransformNotice(body, *(CMD_NOTICE_BODY*)data);
            break;
        case CMD_NOTICE_RESP:
            return TransformNoticeResp(body, *(CMD_NOTICE_RESP_BODY*)data);
            break;
        case CMD_USER_ADD_DEV:
            return TransformUserAddDev(body, *(CMD_USER_ADD_DEV_BODY*)data);
            break;
        case CMD_USER_ADD_DEV_RESP:
            return TransformUserAddDevResp(body, *(CMD_USER_ADD_DEV_RESP_BODY*)data);
            break;
        case CMD_USER_DEL_DEV:
            return TransformUserDelDev(body, *(CMD_USER_DEL_DEV_BODY*)data);
            break;
        case CMD_USER_DEL_DEV_RESP:
            return TransformUserDelDevResp(body, *(CMD_USER_DEL_DEV_RESP_BODY*)data);
            break;
        case CMD_GETLIST:
            return TransformGetList(body, *(CMD_GETLIST_BODY*)data);
            break;
        case CMD_GETLIST_RESP:
            return TransformGetListResp(body, *(CMD_GETLIST_RESP_BODY*)data);
            break;
        case CMD_GETSTATUS:
            return TransformGetStatus(body, *(CMD_GETSTATUS_BODY*)data);
            break;
        case CMD_GETSTATUS_RESP:
            return TransformGetStatusResp(body, *(CMD_GETSTATUS_RESP_BODY*)data);       
            break;
        case CMD_ECHO:
            return TransformEcho(body, *(CMD_ECHO_BODY*)data);
            break;
        case CMD_ECHO_RESP:
            return TransformEchoResp(body, *(CMD_ECHO_RESP_BODY*)data);
            break;
        default:
            return -1;
    }
    return 0;
}

int packProtocolBody(ProtocolBody &body , CMD cmd , void *data){
    switch (cmd) {
        case CMD_USER_REGISTER:
            return PackUserRegister(body, *(CMD_USER_REGISTER_BODY*)data);
        case CMD_USER_REGISTER_RESP:
            return PackUserRegisterResp(body, *(CMD_USER_REGISTER_RESP_BODY*)data);
        case CMD_USER_LOGIN:
            return PackUserLogin(body, *(CMD_USER_LOGIN_BODY*)data);
        case CMD_USER_LOGIN_RESP:
            return PackUserLoginResp(body, *(CMD_USER_LOGIN_RESP_BODY*)data);
        case CMD_USER_LOGOUT:
            return PackUserLogout(body, *(CMD_USER_LOGOUT_BODY*)data);
        case CMD_USER_LOGOUT_RESP:
            return PackUserLogoutResp(body, *(CMD_USER_LOGOUT_RESP_BODY*)data);
        case CMD_DEV_LOGIN:
            return PackDevLogin(body, *(CMD_DEV_LOGIN_BODY*)data);
        case CMD_DEV_LOGIN_RESP:
            return PackDevLoginResp(body, *(CMD_DEV_LOGIN_RESP_BODY*)data);
        case CMD_DEV_LOGOUT:
            return PackDevLogout(body, *(CMD_DEV_LOGOUT_BODY*)data);
        case CMD_DEV_LOGOUT_RESP:
            return PackDevLogoutResp(body, *(CMD_DEV_LOGOUT_RESP_BODY*)data);
        case CMD_HEART:
            return PackHeart(body, *(CMD_HEART_BODY*)data);
        case CMD_HEART_RESP:
            return PackHeartResp(body, *(CMD_HEART_RESP_BODY*)data);
        case CMD_MSG:
            return PackMsg(body, *(CMD_MSG_BODY*)data);
        case CMD_MSG_RESP:
            return PackMsgResp(body, *(CMD_MSG_RESP_BODY*)data);
        case CMD_NOTICE:
            return PackNotice(body, *(CMD_NOTICE_BODY*)data);
        case CMD_NOTICE_RESP:
            return PackNoticeResp(body, *(CMD_NOTICE_RESP_BODY*)data);
        case CMD_USER_ADD_DEV:
            return PackUserAddDev(body, *(CMD_USER_ADD_DEV_BODY*)data);
        case CMD_USER_ADD_DEV_RESP:
            return PackUserAddDevResp(body, *(CMD_USER_ADD_DEV_RESP_BODY*)data);
        case CMD_USER_DEL_DEV:
            return PackUserDelDev(body, *(CMD_USER_DEL_DEV_BODY*)data);
        case CMD_USER_DEL_DEV_RESP:
            return PackUserDelDevResp(body, *(CMD_USER_DEL_DEV_RESP_BODY*)data);
        case CMD_GETLIST:
            return PackGetList(body, *(CMD_GETLIST_BODY*)data);
        case CMD_GETLIST_RESP:
            return PackGetListResp(body, *(CMD_GETLIST_RESP_BODY*)data);
        case CMD_GETSTATUS:
            return PackGetStatus(body, *(CMD_GETSTATUS_BODY*)data);
        case CMD_GETSTATUS_RESP:
            return PackGetStatusResp(body, *(CMD_GETSTATUS_RESP_BODY*)data);
        case CMD_ECHO:
            return PackEcho(body, *(CMD_ECHO_BODY*)data);
        case CMD_ECHO_RESP:
            return PackEchoResp(body , *(CMD_ECHO_RESP_BODY*)data);
        default:
            return -1;
    }
    return 0;
}