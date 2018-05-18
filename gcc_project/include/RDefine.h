/*
 * RDefine.h
 *
 *  Created on: 2016-12-22
 *      Author: OnlyMe
 */

#ifndef RDEFINE_H_
#define RDEFINE_H_

#define TRUE   1
#define FALSE  0


//SCICCR
#define SCI_STOPBITS_ONE   0
#define SCI_STOPBITS_TWO   1
#define SCI_PARITY_ODD     0
#define SCI_PARITY_EVEN    1
#define SCI_PARITY_DIS     0
#define SCI_PARITY_EN      1
#define SCI_LOOPBACK_DIS   0
#define SCI_LOOPBACK_EN    1
#define SCI_MODE_IDLE      0
#define SCI_MODE_ADDR      1
#define SCI_CHARLENGTH_1   0
#define SCI_CHARLENGTH_2   1
#define SCI_CHARLENGTH_3   2
#define SCI_CHARLENGTH_4   3
#define SCI_CHARLENGTH_5   4
#define SCI_CHARLENGTH_6   5
#define SCI_CHARLENGTH_7   6
#define SCI_CHARLENGTH_8   7

//SCICTL1
#define SCI_RXERR_INT_EN   1
#define SCI_RXERR_INT_DIS  0
#define SCI_SW_RESET_EN    0
#define SCI_SW_RESET_DIS   1
#define SCI_LINEIDLE_OR_SETADDR  1
#define SCI_SLEEP_MODE_EN  1
#define SCI_SLEEP_MODE_DIS 0
#define SCI_TX_EN 		   1
#define SCI_TX_DIS		   0
#define SCI_RX_EN		   1
#define SCI_RX_DIS		   0

//SCICTL2
#define SCI_RX_BK_INT_EN   1
#define SCI_RX_BK_INT_DIS  0
#define SCI_TX_INT_EN      1
#define SCI_TX_INT_DIS     0

//SCIFFTX
#define SCI_RESET_EN       0
#define SCI_RESET_DIS      1
#define SCI_FIFO_EN        1
#define SCI_FIFO_DIS       0
#define SCI_TXFIFO_RESET_EN   0
#define SCI_TXFIFO_RESET_DIS  1
#define SCI_TXFIFO_INTF_CLR  1
#define SCI_TXFIFO_INT_EN  1
#define SCI_TXFIFO_INT_DIS 0
#define SCI_TXFIFO_INTLEVEL_0  0
#define SCI_TXFIFO_INTLEVEL_1  1
#define SCI_TXFIFO_INTLEVEL_2  2
#define SCI_TXFIFO_INTLEVEL_3  3
#define SCI_TXFIFO_INTLEVEL_4  4
#define SCI_TXFIFO_INTLEVEL_5  5
#define SCI_TXFIFO_INTLEVEL_6  6
#define SCI_TXFIFO_INTLEVEL_7  7
#define SCI_TXFIFO_INTLEVEL_8  8
#define SCI_TXFIFO_INTLEVEL_9  9
#define SCI_TXFIFO_INTLEVEL_10  10
#define SCI_TXFIFO_INTLEVEL_11  11
#define SCI_TXFIFO_INTLEVEL_12  12
#define SCI_TXFIFO_INTLEVEL_13  13
#define SCI_TXFIFO_INTLEVEL_14  14
#define SCI_TXFIFO_INTLEVEL_15  15
#define SCI_TXFIFO_INTLEVEL_16  16

//SCIFFRX
#define SCI_RXFIFO_OVERFLOW_CLR 1
#define SCI_RXFIFO_RESET_EN    0
#define SCI_RXFIFO_RESET_DIS   1
#define SCI_RXFIFO_INTF_CLR  1
#define SCI_RXFIFO_INT_EN  1
#define SCI_RXFIFO_INT_DIS 0
#define SCI_RXFIFO_INTLEVEL_0  0
#define SCI_RXFIFO_INTLEVEL_1  1
#define SCI_RXFIFO_INTLEVEL_2  2
#define SCI_RXFIFO_INTLEVEL_3  3
#define SCI_RXFIFO_INTLEVEL_4  4
#define SCI_RXFIFO_INTLEVEL_5  5
#define SCI_RXFIFO_INTLEVEL_6  6
#define SCI_RXFIFO_INTLEVEL_7  7
#define SCI_RXFIFO_INTLEVEL_8  8
#define SCI_RXFIFO_INTLEVEL_9  9
#define SCI_RXFIFO_INTLEVEL_10  10
#define SCI_RXFIFO_INTLEVEL_11  11
#define SCI_RXFIFO_INTLEVEL_12  12
#define SCI_RXFIFO_INTLEVEL_13  13
#define SCI_RXFIFO_INTLEVEL_14  14
#define SCI_RXFIFO_INTLEVEL_15  15
#define SCI_RXFIFO_INTLEVEL_16  0x1F

//SCIFFCT
#define SCI_ABD_FLAG_CLR  1
#define SCI_ABD_EN        1
#define SCI_ABD_DIS       0
#define SCI_TXFIFO_DELAY(x)   x

//SCIPRI
#define SCI_STOP_IMMEDIATE    0
#define SCI_STOP_AFTER_TX_RX  2
#define SCI_FREE_RUN          3




#endif /* RDEFINE_H_ */
