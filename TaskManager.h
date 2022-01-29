/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef __TASKMANAGER_H__    /* Guard against multiple inclusion */
#define __TASKMANAGER_H__

void TMAN_Init(int);
void TMAN_Close(void);
void TMAN_TaskAdd();
void TMAN_TaskRegisterAtributes(void);
void TMAN_TaskWaitPeriod(void);
void TMAN_TaskStats(void);

#endif 