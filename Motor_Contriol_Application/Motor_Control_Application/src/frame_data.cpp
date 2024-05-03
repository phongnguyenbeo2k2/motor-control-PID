#include "frame_data.h"

frame_data::frame_data(QObject *parent)
    : QObject{parent}
{
    read_data.clear();
    write_data.clear();
    length_frame_data_rx = 0;
    length_frame_data_tx = 0;
}

void frame_data::test_frame()
{
    qDebug() << "HELLO";
}

uint8_t frame_data::create_frame_data(uint8_t const *data_src, uint8_t length_raw_data, uint8_t *data_des)
{
    uint16_t count_ESC = 0;
    uint16_t crc = 0;
    *(data_des ++) = S_OF;
    for (int i = 0; i < length_raw_data; i++)
    {
        if ((*(data_src+i)) == S_OF || (*(data_src+i) == ESC) || (*(data_src + i) == E_OF))
        {
            *(data_des++) = ESC;
            crc = crc16_floating(*(data_des - 1),crc);
            *(data_des++) = *(data_src + i) ^ 0x20;
            crc = crc16_floating(*(data_des - 1),crc);
            count_ESC ++;
        }
        else
        {
            crc = crc16_floating(*(data_src + i),crc);
            *(data_des++) = *(data_src+i);
        }
    }
    *(data_des++) = (uint8_t) (crc);
    *(data_des++) = (uint8_t) (crc >> 8);
    *(data_des) = E_OF;
    return ((length_raw_data) + count_ESC + 4);
}

int8_t frame_data::decode_received_frame_data(uint8_t const *data_src, uint8_t length_received_data, uint8_t *data_des, uint8_t *length_raw_data)
{
    uint8_t start_check_frame = 0;
    uint8_t index = 0;
    uint8_t find_end_frame = 0;
    uint8_t const *p_start_check = data_src;
    uint16_t crc_check = 0;
    uint8_t count_raw_data = 0;
    int check = 0;
//    qDebug() << "received_data_from_STM32 1.2.1";/**/
    for (volatile int i = 0; i < length_received_data; i++)
    {
//        qDebug() << "received_data_from_STM32 1.2.2";
        if (*(data_src + i) == S_OF)
        {
            start_check_frame = 1;
            index = i + 1;
            break;
        }
    }
//    qDebug() << "received_data_from_STM32 1.2.3";
    p_start_check += index;
    if (start_check_frame == 1)
    {
//        qDebug() << "received_data_from_STM32 1.2.4";
        for (volatile int i = 0; i < length_received_data; i++)
        {
//            qDebug() << "received_data_from_STM32 1.2.5";
            if ((*(p_start_check + i) == E_OF) && (*(p_start_check + i - 1) != ESC))
            {
//                qDebug() << "received_data_from_STM32 1.2.6";
                index = i;
                find_end_frame = 1;
                break;
            }
        }
//        qDebug() << "received_data_from_STM32 1.2.7";
        if (find_end_frame == 1)
        {
//            qDebug() << "received_data_from_STM32 1.2.8";
            uint8_t test_1 = *(p_start_check + index - 2);
            while (*(p_start_check) != test_1)
            {
//                qDebug() << "received_data_from_STM32 1.2.9";

                if ((*(p_start_check)) == ESC)
                {
                    crc_check = crc16_floating(*(p_start_check), crc_check);
                    *(data_des++) = *(++p_start_check) ^ (0x20);
                    crc_check = crc16_floating(*(p_start_check), crc_check);
                }
                else
                {
                    crc_check = crc16_floating(*(p_start_check), crc_check);
                    *(data_des++) = *(p_start_check);
                }
                p_start_check++;
                count_raw_data++;
                check ++;
                if (check > 20)
                {
                    break;
                }
            }
//            qDebug() << "received_data_from_STM32 1.2.10";
            uint8_t crc_1 = (uint8_t)crc_check;
            uint8_t crc_2 = (uint8_t)(crc_check >> 8);
            if (!(crc_1 == *(p_start_check) && crc_2 == *(p_start_check + 1)))
            {
//                qDebug() << "received_data_from_STM32 1.2.11";
                return EEROR_FRAME;
            }else
            {
                qDebug() << "received_data_from_STM32 1.2.12";
                *length_raw_data = count_raw_data;
                return TRUE_FRAME;
            }
        }else
        {
            return EEROR_FRAME;
        }
    }
    else
    {
        return EEROR_FRAME;
    }
}

void frame_data::clear_frame_tx()
{
    /*clear frame transmit*/
    for (int i = 0; i < MAX_FRAME_DATA_TX; i++)
    {
        frame_data_tx[i] = 0;
    }
}

void frame_data::clear_frame_rx()
{
    /*clear frame receive*/
    for (int i = 0; i < MAX_FRAME_DATA_RX; i++)
    {
        frame_data_rx[i] = 0;
    }
}
