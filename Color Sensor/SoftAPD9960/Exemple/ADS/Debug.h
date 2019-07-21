#ifndef _DEBUG_
#define _DEBUG_

#define PRINTLN(msg) Serial.println(msg)
#define PRINT(msg) Serial.print(msg)
#define PRINT2(param,val) Serial.print(param);Serial.print(": "); Serial.print((uint16_t)val);Serial.write(9)
#define IFPRINT(condicao,msgDef,msgOK,msgNOK) PRINT(F(msgDef));PRINTLN((condicao)?(F(msgOK)):F(msgNOK))

#endif

