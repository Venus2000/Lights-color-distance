# Lights-color-distance
คือ ระบบดูแลความปลอดภัยของการถอยรถจอดรถหรือดูระยะของรถที่เข้าใกล้ด้วยเทคโนโลยีระบบsensor

## ที่มาและความสำคัญ
ในการขับขี่รถยนต์การเดินทางในที่ต่างๆไม่ว่าจะจอดถอยรถทุกคนย่อมต้องการความปลอดภัยในกาขับขี่รถยนต์นั้นมักจะพบปัญหาในการที่เราจะต้องถอยจอดรถคันใหญ่ๆหรือคันเล็กเข้าซองโดยที่ไม่ไปชนรถคันอื่นให้เกิดความเสียหาย

ด้วยเหตุนี้และปัจจุบันทำให้ผู้จัดทำได้เล็งเห็นว่าการประยุกต์ใช้ UItrasonic Distance Sensor ร่วมกับ 2.4 TFT Resistive Touch HMI Screen และตัวไฟ RGB โดยนำมาประมวลผล สั่งการให้Sensor ทำงานควบคุมระยะทางเวลาถอยรถหรือมีรถเข้าใกล้เรามากขนาดไหน จะแสดงสีไฟตามระยะและทำการบอกบนจอ HMI และยังสามารถปรับความสว่างของแสงได้อีกด้วย

## กลุ่มเป้าหมาย
    -บุคคลทั่วไปที่ต้องการระบบช่วยดูแลความปลอดภัยภายนอกบ้าน
    -ผู้ใหญ่ทุกวัยที่ต้องการระบบช่วยความสะดวกในการถอยรถโดยมีสัญญาณไฟแจ้งเตือนเป็นระยะๆ
    -บุคคลทั่วไปที่ต้องการเป็นตัวช่วยในการแจ้งเตือนภัยโดยการแสดงสีของไฟตามระยะ
## รายละเอียดโปรเจค
    
### Perception Module
    -UItrasonic Distance Sensor
    -2.4 TFT Resistive Touch HMI Screen
    
### Behavior
    -ทำการปรับแสงลดแสงผ่านจอ 2.4 TFT Resistive Touch HMI Screen
    -Sensor ทำการจับระยะของวัตถุที่กำลังจะเข้าใกล้
    -รับข้อมูลจากSensorแล้วหลอดไฟRGB จะทำการแสดงค่าสีตามระยะออกมา
    -เมื่อได้รับข้อมูลจากทั้งสองคือSensor และ ไฟRGB แล้วจะทำการแสดงผลออกจากทางหน้าจอ
### Manipulation
    -2.4 TFT Resistive Touch HMI Screen
    -ไฟRGB แสดงทั้งหมดสามสี
### โครงสร้างพื้นฐาน
![flowchart](https://user-images.githubusercontent.com/61343632/84478874-361e3580-acbc-11ea-9d88-d1005443c76d.jpg)
### ระบบการทำงาน
![diagram](https://user-images.githubusercontent.com/61343632/84479649-83e76d80-acbd-11ea-93c8-f67b12aa7507.jpg)



