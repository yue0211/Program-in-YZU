package com.example.chatroom.Model;

public class Group {

    private String id;
    private String username;
    private String imageURL;
    private String oshi_name;
    private String oshi_from;


    public Group(String id, String username, String imageURL, String oshi_name, String oshi_from) {
        this.id = id;
        this.username = username;
        this.imageURL = imageURL;
        this.oshi_name = oshi_name;
        this.oshi_from = oshi_from;
    }


    public Group()
    {
        id = "";
        username = "";
        imageURL = "";
        oshi_name = "";
        oshi_from = "";
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getImageURL() {
        return imageURL;
    }

    public void setImageURL(String imageURL) {
        this.imageURL = imageURL;
    }

    public String getOshi_name() {
        return oshi_name;
    }

    public void setOshi_name(String oshi_name) {
        this.oshi_name = oshi_name;
    }

    public String getOshi_from() {
        return oshi_from;
    }

    public void setOshi_from(String oshi_from) {
        this.oshi_from = oshi_from;
    }

}

