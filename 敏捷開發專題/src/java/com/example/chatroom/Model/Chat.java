package com.example.chatroom.Model;

import java.util.ArrayList;

public class Chat {


    private String sender;
    private String receiver;
    private String message;
    private boolean isseen;
    private String Date;
    private String Time;
    private String type;

    private String userCantSee;

    private String emoji_smile;
    private String emoji_love;
    private String emoji_cry;
    private String emoji_angry;
    private String emoji_nothing;
    private String emoji_good;

    public String getEmoji_smile() {
        return emoji_smile;
    }

    public String getEmoji_good() {
        return emoji_good;
    }

    public void setEmoji_good(String emoji_good) {
        this.emoji_good = emoji_good;
    }

    public String getEmoji_cry() {
        return emoji_cry;
    }

    public String getEmoji_nothing() {
        return emoji_nothing;
    }

    public void setEmoji_nothing(String emoji_nothing) {
        this.emoji_nothing = emoji_nothing;
    }

    public String getEmoji_angry() {
        return emoji_angry;
    }

    public void setEmoji_angry(String emoji_angry) {
        this.emoji_angry = emoji_angry;
    }

    public void setEmoji_cry(String emoji_cry) {
        this.emoji_cry = emoji_cry;
    }

    public String getEmoji_love() {
        return emoji_love;
    }

    public void setEmoji_love(String emoji_love) {
        this.emoji_love = emoji_love;
    }

    public void setEmoji_smile(String emoji_smile) {
        this.emoji_smile = emoji_smile;
    }



    public String getUserCantSee() {
        return userCantSee;
    }

    public void setUserCantSee(String userCantSee) {
        this.userCantSee = userCantSee;
    }

    public Chat(String sender, String receiver, String message, boolean isseen, String Date, String Time) {
        this.sender = sender;
        this.receiver = receiver;
        this.message = message;
        this.isseen = isseen;
        this.Date = Date;
        this.Time = Time;
        this.userCantSee = "";

        this.emoji_smile = "";
        this.emoji_love = "";
        this.emoji_cry = "";
        this.emoji_angry = "";
        this.emoji_nothing = "";
        this.emoji_good = "";
    }

    public Chat(){
    }

    public String getDate() {
        return Date;
    }

    public void setDate(String date) {
        Date = date;
    }

    public String getTime() {
        return Time;
    }

    public void setTime(String time) {
        Time = time;
    }

    public String getSender() {
        return sender;
    }

    public void setSender(String sender) {
        this.sender = sender;
    }

    public String getReceiver() {
        return receiver;
    }

    public void setReceiver(String receiver) {
        this.receiver = receiver;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }


    public boolean isIsseen() {
        return isseen;
    }

    public void setIsseen(boolean isseen) {
        this.isseen = isseen;
    }
    public String getType() {
            return type;
        }
    public void setType(String type) {
                     this.type = type;
}
}
