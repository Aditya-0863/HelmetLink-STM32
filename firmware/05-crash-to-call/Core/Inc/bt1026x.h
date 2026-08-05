#ifndef BT1026X_H
#define BT1026X_H

void bt1026x_init(void);
void bt1026x_power_on(void);
void bt1026x_send_cmd(const char *cmd);
char bt1026x_read(void);

#endif
