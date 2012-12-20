/*******************************************************************************
 
 def.h
 
 author: Spencer Salazar - spencer@ccrma.stanford.edu
 
 ******************************************************************************/


#ifndef __DEF_H__
#define __DEF_H__


#define SAFE_DELETE(x) do{ if(x!=0x0){ delete x; x = 0x0; } } while(0)
#define SAFE_DELETE_V(x) do{ if(x!=0x0){ delete[] x; x = 0x0; } } while(0)


#endif // __DEF_H__


