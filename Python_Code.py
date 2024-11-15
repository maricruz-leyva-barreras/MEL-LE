import time
import threading

import cv2
import numpy as np
import face_recognition
import serial


face_detected = False
state = False
ser = serial.Serial('COM10', 115200)
average = 0
face_confidence_accuracy_values = []


#serial_lock = threading.Lock()

def measure_distance_thread(ser, command): #retrieve the data from Arduino serial communication

        ser.write(command)
        #time.sleep(0.1)
        distance_str = ser.readline().decode('utf-8').strip()
        distance_str = ''.join(filter(str.isdigit, distance_str))
        return int(distance_str)



def measure_firstdistance(): #retrieve the data for first ultrasonic senosors
    return measure_distance_thread(ser, b'T')





# ...
def measure_seconddistance():#retrieve the data for second ultrasonic senosors
    return measure_distance_thread(ser, b'G')





def measure_thirddistance():#retrieve the data for third ultrasonic senosors

  return measure_distance_thread(ser, b'Y')




# ...




def measure_forthdistance():#retrieve the data for forth ultrasonic senosors

  return measure_distance_thread(ser, b'a')








def measure_fifthdistance():#retrieve the data for fifth ultrasonic senosors

  return measure_distance_thread(ser, b'b')







def measure_sixthdistance():#retrieve the data for sixth ultrasonic senosors

  return measure_distance_thread(ser, b'c')





def measure_seventhdistance():#retrieve the data for seventh ultrasonic senosors

  return measure_distance_thread(ser, b'd')



def measure_eightdistance():#retrieve the data for eighth ultrasonic senosors

  return measure_distance_thread(ser, b'e')

def measure_distance(obj_width, focal_length, actual_width):
   return (actual_width * focal_length) / obj_width

# def autonomous_scan():
#     if duration2 > 50 and duration3 > 50 and duration8 > 50:
#         ser.write(b'B')
#         time.sleep(0.1)
#         ser.write(b'E')
#         time.sleep(0.1)
#         ser.write(b'D')
#         time.sleep(0.1)

# def millis():
#     return int(round(time.time() * 1000))

def backward_left(): #the function for going backward if the ultrasonic sensor is too closed to the obstacle, less than 30
    ser.write(b'K')
    time.sleep(0.1)
    ser.write(b'f')
    time.sleep(2.5)
    ser.write(b'F')
    time.sleep(0.1)


def obstacle_avoidance(): #logical function for object avoidace
    if (duration2 > 80 or duration3 > 80) or duration8 > 80:
        ser.write(b'B')
        time.sleep(0.3)
        ser.write(b'F')
        time.sleep(0.1)
        print("STRAIGHT")

    # elif 30 <= duration2 <= 80 or 30 <= duration3 <= 80 and 30 <= duration8 <= 80:
    #     ser.write(b'F')
    #     time.sleep(0.1)
    #     backward_left()
    #     print("BACKWARD")

    elif 30 <= duration2 <= 80 or duration3 > 80 and duration1 > 80:
        ser.write(b'E')
        time.sleep(2)
        ser.write(b'F')
        time.sleep(0.1)
        print("LEFT")


    elif duration2 > 80 or 30 <= duration3 <= 80 and duration4 > 80:
        ser.write(b'D')
        time.sleep(2)
        ser.write(b'F')
        time.sleep(0.1)
        print("RIGHT")
    elif duration2 < 30 or duration3 < 30 or duration8 < 30:
        backward_left()
        print("BACKWARD")



#def center_obstacle():
    #if duration8 > 200:
     #   autonomous_scan()
    #elif duration8 < 200:
        #ser.write(b'F')
#FOR THE DC MOTOR
def forward_movement():#logical functon for forward movement, retrieve the data for all the DC motors from Arduino
    ser.write(b'B')
    time.sleep(0.3)
    ser.write(b'F')
    time.sleep(0.1)


def left_movement():#logical functon for left movement, retrieve the data for all the DC motors from Arduino
    ser.write(b'E')
    time.sleep(1)
    ser.write(b'D')
    time.sleep(1)
    ser.write(b'F')
def right_movement():#logical functon for right movement, retrieve the data for all the DC motors from Arduino
    ser.write(b'D')
    time.sleep(1)
    ser.write(b'E')
    time.sleep(1)
    ser.write(b'F')


# Load YOLO model and its configuration file
net = cv2.dnn.readNet('C:/Users/thong/Downloads/yolov3.weights', 'C:/Users/thong/Downloads/yolov3.cfg')
classes = []
with open('C:/Users/thong/Downloads/coco.names', 'r') as f:
   classes = [line.strip() for line in f.readlines()]


layer_names = net.getLayerNames()
output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers()]


# Load face recognition model
face_image = face_recognition.load_image_file("C:/Users/thong/OneDrive/Desktop/unnamed.jpg")
known_face_encodings = [face_recognition.face_encodings(face_image)[0]]
known_face_names = ["Thong"]

#additional face
additional_face_image = face_recognition.load_image_file("C:/Users/thong/OneDrive/Desktop/unnamed.jpg")
additional_face_encoding = face_recognition.face_encodings(additional_face_image)[0]
known_face_encodings.append(additional_face_encoding)
known_face_names.append("Avery")
# Open cameras
cap = cv2.VideoCapture(0)
cap2 = cv2.VideoCapture(1)
cap3 = cv2.VideoCapture(3)


# Constants for distance estimation
obj_actual_width = 5  # Actual width of the object in centimeters (adjust as needed)
focal_length = 600     # Focal length of the camera (adjust as needed)


while True:
   #RANDOMLY MOVEMENT:
   #autonomous_scan()











   duration1 = measure_firstdistance()
   print(f"Distance 1: {duration1} cm")

   duration2 = measure_seconddistance()
   print(f"Distance 2: {duration2} cm")

   duration3 = measure_thirddistance()
   print(f"Distance 3: {duration3} cm")

   duration4 = measure_forthdistance()
   print(f"Distance 4: {duration4} cm")

   duration5 = measure_fifthdistance()
   #print(f"Distance 5: {duration5} cm")

   duration6 = measure_sixthdistance()
   #print(f"Distance 6: {duration6} cm")

   duration7 = measure_seventhdistance()
   #print(f"Distance 7: {duration7} cm")

   duration8 = measure_eightdistance()
   print(f"Distance 8: {duration8} cm")
   #autonomous_scan()

   obstacle_avoidance()

   print("Randomly seraching")
   face_detected = False


   # Read frames from the cameras
   ret, frame = cap.read()
   ret2, frame2 = cap2.read()
   ret3, frame3 = cap3.read()


   # Process frame from the first camera
   height, width, channels = frame.shape
   blob = cv2.dnn.blobFromImage(frame, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
   net.setInput(blob)
   outs = net.forward(output_layers)


   # Information to be printed for each detected object
   detected_objects = []
   name = "Unknown"  # Initialize the name variable


   # Loop through the detected objects
   #CVS BOTTLE DETECTION ONLY
   for out in outs:
       state = False
       for detection in out:
           scores = detection[5:]
           class_id = np.argmax(scores)
           confidence = scores[class_id]
           if confidence > 0.85:  # if the pill bottle detection is greater than 85 percent
               center_x, center_y, w, h = (detection[0:4] * np.array([width, height, width, height])).astype('int')
               x, y = int(center_x - w / 2), int(center_y - h / 2)


               # Draw rectangle around the detected object
               cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)


               # Measure and store the distance to the detected object
               distance_to_object = measure_distance(w, focal_length, obj_actual_width)
               detected_objects.append({'class': classes[class_id], 'distance': distance_to_object})
               if classes[class_id] == "cup":  # detects CVS bottle
                   state = True
                   print(f"CVS Bottle detected at Distance: {distance_to_object:.2f} cm")
                   bottle_detected_x= (x+w)//2
                   image_bottle_detected_x = width//2
                   position="Center"


                   if bottle_detected_x == image_bottle_detected_x - width // 6:
                       position="Center"
                       print("Center")


                   elif bottle_detected_x < image_bottle_detected_x - width // 6:
                       position = "Left"
                       print("Left")
                   #put the if statement in the function that measuring the distance between the camera and the object


                   elif bottle_detected_x > image_bottle_detected_x + width // 6:
                       position = "Right"
                       print("Right")

               elif classes[class_id] != "cup":#the original goal was to obstacle detection; however, only use ultrasonic senosrs
                   print(f"Obstacle is ahead at Distance: {distance_to_object:.2f} cm")
                   area = w*h
                   obstacle_detected_x = (x + w) // 2
                   image_obstacle_detected_x = width // 2
                   position = "Center"
                   print(area)
                   if  area < 150000:
                       if distance_to_object < 10:
                           ser.write(b'F')
                           print("Stop")
                   elif area > 150000:
                       if distance_to_object < 20:
                           ser.write(b'F')
                           print("Stop")






                   if obstacle_detected_x < image_obstacle_detected_x - width // 6:
                       position = "Left"
                       print("Left")
                       print(area)





                   # put the if statement in the function that measuring the distance between the camera and the object

                   elif obstacle_detected_x > image_obstacle_detected_x + width // 6:
                       position = "Right"
                       print("Right")
                       print(area)




















                   #if distance_to_object < 25.0: #and add ULTRASONIC SENSOR DISTANCE < 5:
                       #if position == "Center":
                        #   print("Back up ")
                       #elif position == "Left":
                        #   print("Merge right")
                       #elif position == "Right":
                        #   print("Merge left")


   if not detected_objects: #OBJECT AVOIDANCE IN CASE THE CAMERA DOEST DETECT THE OBSTACLE
       print("Nothing is detected")
       #left_obstacle()
       #right_obstacle()


       #make another fucntion that adds with ultrasonic sensor in order to detect the distance of ultrasonic
   # Check conditions for the first camera




   # Process frame from the second camera
   height2, width2, channels2 = frame2.shape
   blob2 = cv2.dnn.blobFromImage(frame2, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
   net.setInput(blob2)
   outs2 = net.forward(output_layers)


   # Information to be printed for each detected object from the second camera
   detected_objects2 = []
   name2 = "Unknown"  # Initialize the name2 variable


   # Loop through the detected objects from the second camera. which is for Face Detection only
   for out2 in outs2:
       for detection2 in out2:
           scores2 = detection2[5:]
           class_id2 = np.argmax(scores2)
           confidence2 = scores2[class_id2]
           if confidence2 > 0.95:  # if the Face detection is greater than 95 percent
               center_x2, center_y2, w2, h2 = (detection2[0:4] * np.array([width2, height2, width2, height2])).astype('int')
               x2, y2 = int(center_x2 - w2 / 2), int(center_y2 - h2 / 2)


               # Draw rectangle around the detected object from the second camera
               cv2.rectangle(frame2, (x2, y2), (x2 + w2, y2 + h2), (0, 255, 0), 2)


               # Measure and store the distance to the detected object from the second camera
               distance_to_object2 = measure_distance(w2, focal_length, obj_actual_width)
               detected_objects2.append({'class': classes[class_id2], 'distance': distance_to_object2})
               if classes[class_id2] == "cup":
                   print(f"Cup detected at Distance: {distance_to_object2:.2f} cm")


               if classes[class_id2] == "person": #FOLLOW THE PERSON
                   num_detection = 0

                   # Calculate the confusion matrix by taking the average of all the face accuracy percentage
                   face_locations2 = face_recognition.face_locations(frame2)
                   face_encodings2 = face_recognition.face_encodings(frame2, face_locations2)
                   face_confidence = confidence2* 100
                   print(f"Face confidence accuracy is : {face_confidence:.2f} ")
                   num_detection+=1
                   face_confidence_accuracy_values.append(face_confidence)
                   average= sum(face_confidence_accuracy_values)/len(face_confidence_accuracy_values)



                   for face_encoding2 in face_encodings2:
                       matches2 = face_recognition.compare_faces(known_face_encodings, face_encoding2)


                       if True in matches2:

                           first_match_index2 = matches2.index(True)
                           name2 = known_face_names[first_match_index2]
                           if name2 == "Thong" or name2 == "Avery": #check whether the robot could recognize Thong and Avery so the robot can follow based on the logical function below
                               face_center_x2 = (x2 + w2 // 2)  # X-coordinate of the center of the detected face
                               image_center_x2 = width2 // 2  # X-coordinate of the center of the image
                               position = "Center"
                               forward_movement()

                               if face_center_x2 < image_center_x2 - width2 // 6:
                                   position = "Left"
                                   print("Merge Left")
                                   left_movement()
                               elif face_center_x2 > image_center_x2 + width2 // 6:
                                   position = "Right"
                                   print("Merge Right")
                                   right_movement()

                       print(f"Person detected from the second camera: {name2}, Distance: {distance_to_object2:.2f} cm")
   print("The average accuaracy for face confidence is: ", average)


               #elif classes[class_id2] == "person" and duration8 < 20: #STOP
                #   ser.write(b'F')
                 #  time.sleep(20)


       # Information to be printed for each detected object from the second camera , FOR OBJECT AVOIDANCE, LEAVE IT IF NOT USING IT
   height3, width3, channels3 = frame3.shape
   blob3 = cv2.dnn.blobFromImage(frame3, 0.00392, (416, 416), (0, 0, 0), True, crop=False)
   net.setInput(blob3)
   outs3 = net.forward(output_layers)
   detected_objects3 = []
   name3 = "Unknown"  # Initialize the name2 variable


   # Loop through the detected objects from the second camera
   for out3 in outs3:
       for detection3 in out3:
           scores3 = detection3[5:]
           class_id3 = np.argmax(scores3)
           confidence3 = scores3[class_id3]
           if confidence3 > 0.5:  # Adjust confidence threshold as needed
               center_x3, center_y3, w3, h3 = (detection3[0:4] * np.array([width3, height3, width3, height3])).astype(
                   'int')
               x3, y3 = int(center_x3 - w3 / 2), int(center_y3 - h3 / 2)

               # Draw rectangle around the detected object from the second camera
               cv2.rectangle(frame3, (x3, y3), (x3 + w3, y3 + h3), (0, 255, 0), 2)

               # Measure and store the distance to the detected object from the second camera
               distance_to_object3 = measure_distance(w3, focal_length, obj_actual_width)
               detected_objects3.append({'class': classes[class_id3], 'distance': distance_to_object3})
               if classes[class_id3] == "cup":
                   print(f"Cup detected at Distance: {distance_to_object3:.2f} cm")
               else:
                   print(f"Obstacle at Distance: {distance_to_object3:.2f} cm")

   if (name2=="Thong" or name2=="Avery") and duration8 < 30: #If the distance is too closed to the person, stop before hitting the person
       ser.write(b'F')
   # Check condition between the second camera, FACE DETECTION, and the first camera, CVS DETECTION. If they're matched, then execute the arm kinematics to pick up the bottle at right slot
   if (name2 == "Thong" or name2 == "Avery") and any(obj['class'] == "cup" for obj in detected_objects):
       print("Bring the bottle from the second camera")
       if duration7 < 20 and name2 == "Thong":  # CVS pill bottle slot for Thong
           print("Ready to give the bottle to Thong")

           ser.write(b'I')  # servo 2 , turn left 60
           ser.write(b'H')  # servo 3 , 40 degrees forward
           ser.write(b'N')  # servo 1 , close the claw

           time.sleep(0.1)
           ser.write(b'S')  # servo 3
           ser.write(b'W')  # servo 2
           ser.write(b'H')  # servo 3
           ser.write(b'M')  # servo 1
           ser.write(b'S')  # servo 3
       elif duration6 < 5:

           ser.write(b'R')  # servo 2 , turn left 90

           ser.write(b'H')  # servo 3 , 60 degrees forward

           ser.write(b'N')  # servo 1 , close the claw

           time.sleep(0.1)
           ser.write(b'L')  # servo 3

           ser.write(b'W')  # servo 2

           ser.write(b'H')  # servo 3

           ser.write(b'M')  # servo 1

           ser.write(b'L')  # servo 3


       elif duration5 < 20 and name2 == "Avery" : #CVS pill bottle for Avery
           # ser.write(b'B')
           # time.sleep(0.1)
           print("Ready to deivery the bottle to Avery")
           ser.write(b'P')  # servo 2 , turn left 60
           ser.write(b'H')  # servo 3 , 40 degrees forward
           ser.write(b'N')  # servo 1 , close the claw

           time.sleep(0.1)
           ser.write(b'S')  # servo 3
           ser.write(b'W')  # servo 2
           ser.write(b'H')  # servo 3
           ser.write(b'M')  # servo 1
           ser.write(b'S')  # servo 3



       #ACTIVATE ARM KINEMATICS




   # Display the cameras
   cv2.imshow("YOLO Object Detection - Camera 1", frame)
   cv2.imshow("YOLO Object Detection - Camera 2", frame2)
   #cv2.imshow("YOLO Object Detection - Camera 3", frame3)


   # Break the loop if 'q' key is pressed
   if cv2.waitKey(1) & 0xFF == ord('q'):
       break


# Release the captures and close the OpenCV windows
cap.release()
cap2.release()
cv2.destroyAllWindows()
ser.close()

