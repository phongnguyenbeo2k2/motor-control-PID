#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include <QObject>
#include <stdint.h>
#include <QByteArray>
#include <string.h>
#include <stdint.h>
#include <crc16.h>
#include <QDebug>

/*detail information of frame data*/

#define S_OF                    0x55
#define E_OF                    0xAA
#define ESC                     0x7D
#define MAX_RAW_DATA_TX         (4*3 + 2)       /*send PID 4*3 of data and 1 byte for mode, 1 byte for length of raw data*/
#define MAX_RAW_DATA_RX         (4 + 1 + 1)     /*raw data is consist of 4 bytes data for velocity or position and 1 byte mode, 1 byte lenght of raw data */
#define MAX_FRAME_DATA_RX       (MAX_RAW_DATA_RX * 2 + 4)
#define MAX_FRAME_DATA_TX       (MAX_RAW_DATA_TX * 2 + 4)
/*frame check*/
#define TRUE_FRAME               0
#define EEROR_FRAME              1

class frame_data : public QObject
{
    Q_OBJECT
public:
    /*method*/
    explicit frame_data(QObject *parent = nullptr);
    void test_frame();
    uint8_t create_frame_data(uint8_t const *data_src, uint8_t l32ength_raw_data, uint8_t *data_des);
    int8_t  decode_received_frame_data(uint8_t const *data_src,uint8_t *length_received_data, uint8_t *data_des, uint8_t *length_raw_data);
    void clear_frame_tx();
    void clear_frame_rx();
    /*attributes*/
    QByteArray write_data;
    QByteArray read_data;
    uint8_t frame_data_tx[MAX_FRAME_DATA_TX] = {0};
    uint16_t length_frame_data_tx;
    uint8_t frame_data_rx[MAX_FRAME_DATA_RX] = {0};
    uint8_t length_frame_data_rx;
//signals:

//private slots:

};

#endif // FRAME_DATA_H
