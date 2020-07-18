// Auto-generated. Do not edit!

// (in-package telegram_ros.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Options {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.question = null;
      this.options = null;
    }
    else {
      if (initObj.hasOwnProperty('question')) {
        this.question = initObj.question
      }
      else {
        this.question = '';
      }
      if (initObj.hasOwnProperty('options')) {
        this.options = initObj.options
      }
      else {
        this.options = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Options
    // Serialize message field [question]
    bufferOffset = _serializer.string(obj.question, buffer, bufferOffset);
    // Serialize message field [options]
    bufferOffset = _arraySerializer.string(obj.options, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Options
    let len;
    let data = new Options(null);
    // Deserialize message field [question]
    data.question = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [options]
    data.options = _arrayDeserializer.string(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.question.length;
    object.options.forEach((val) => {
      length += 4 + val.length;
    });
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'telegram_ros/Options';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '95c5cf65731d4dcf4593661dbe57ef01';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string question
    string[] options
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Options(null);
    if (msg.question !== undefined) {
      resolved.question = msg.question;
    }
    else {
      resolved.question = ''
    }

    if (msg.options !== undefined) {
      resolved.options = msg.options;
    }
    else {
      resolved.options = []
    }

    return resolved;
    }
};

module.exports = Options;
