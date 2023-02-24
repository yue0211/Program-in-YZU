package com.example.chatroom.Model;

public class User {

    private String id;
    private String username;
    private String imageURL;
    private String status;
    private String search;
    private String email;
    private String oshi_name;
    private String oshi_from;
    private String oshi_reason;
    private String oshi_imageURL;




    public String getOshi_imageURL() {
        return oshi_imageURL;
    }

    public void setOshi_imageURL(String oshi_imageURL) {
        this.oshi_imageURL = oshi_imageURL;
    }


    public User(String id, String username, String imageURL, String status, String search, String email) {
        this.id = id;
        this.username = username;
        this.imageURL = imageURL;
        this.status = status;
        this.search = search;
        this.email = email;
        this.oshi_name = "";
        this.oshi_from = "";
        this.oshi_reason = "";
        this.oshi_imageURL = "default";

    }


    public User()
    {
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
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

    public String getOshi_reason() {
        return oshi_reason;
    }

    public void setOshi_reason(String oshi_reason) {
        this.oshi_reason = oshi_reason;
    }

    public void setOshi_from(String oshi_from) {
        this.oshi_from = oshi_from;
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


    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getSearch() {
        return search;
    }

    public void setSearch(String search) {
        this.search = search;
    }
}

