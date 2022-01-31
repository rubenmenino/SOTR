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

void TMAN_Init();
void TMAN_Close(void);
void TMAN_TaskAdd(TaskHandle_t);
void TMAN_TaskRegisterAtributes(int, int, int, int, int);
void TMAN_TaskWaitPeriod(int);
void TMAN_TaskStats(void);

#endif 