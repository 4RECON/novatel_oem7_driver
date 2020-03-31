import unittest
import rostest
import rosbag

import os

import traceback
from docutils.nodes import topic

def get_topic_list(bag_name):
    """ Return a list of topics stored in this bag """
    bag = rosbag.Bag(bag_name, 'r')
    return bag.get_type_and_topic_info()[1].keys()

def make_msg_gen(bag_name, topic):
    """ Generates a sequence of messages in the topic from the bag """
    bag = rosbag.Bag(bag_name, 'r')
    for top, msg, t in bag.read_messages():
        if top == topic:
            yield msg 

    
    
def compare(ref_msg, uut_msg):
    # Supress seqno, timestamp
    ref_msg.header.seq = 0
    uut_msg.header.seq = 0
    
    ref_msg.header.stamp = None
    uut_msg.header.stamp = None
    
    if(ref_msg != uut_msg):
        print("Messages do not match:")
        print("Reference:------------")
        print(ref_msg)
        print("\n\n\n")
        print("UUT-------------")
        print(uut_msg)
        return False;
    
    return True
    
    
def verify_bag_equivalency(ref_bag, uut_bag):
  """
  Verifies that two bags contain semantically identical sequence of messages.
  """

  ref_topics = get_topic_list(ref_bag)
  print(ref_topics)
  for topic in ref_topics:
      msgno = 0
      uut_gen = make_msg_gen(uut_bag, topic)
      ref_gen = make_msg_gen(ref_bag, topic)
      for ref_msg in ref_gen:
        uut_msg = next(uut_gen)
        if not compare(ref_msg, uut_msg):
            print("\n\n")
            print("Topic: {} Msg No: {}".format(topic, msgno))
            assert False
            
        msgno += 1
      
      print("Verified {} '{}' messages".format(msgno, topic))
      # Check for presence of unexpected messages
      unexpected_messages = 0
      try:
          while True:
              uut_top, uut_msg, uut_t = next(uut_gen)
              print("Unexpected message")
              print(uut_msg)
              unexpected_messages += 1
  
      except StopIteration:
        pass # Normal
      
      except:
        traceback.print_exc()
        assert(False)
        
      assert(unexpected_messages == 0)





  