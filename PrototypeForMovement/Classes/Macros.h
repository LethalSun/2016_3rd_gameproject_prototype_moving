#pragma once
#define CREATE_FUNC_MAKE_ANIMATION(__TYPE__) \
static __TYPE__* create(const char *fileName, const char * fileNameExtention) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init(fileName, fileNameExtention)) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}