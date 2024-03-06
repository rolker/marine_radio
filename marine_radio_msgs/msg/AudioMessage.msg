# Represents a complete radio audio transmission.
#
# header.stamp may indicate the reception time of a radio message or 
# a future schedled time for a message to be transmitted. In either case
# the stamp should be associated with the begining of the data
# 
# header.frame_id may be used to indicate the frame of the relevan radio antenna
std_msgs/Header             header

marine_radio_msgs/AudioData audio_data
audio_common_msgs/AudioInfo audio_info
