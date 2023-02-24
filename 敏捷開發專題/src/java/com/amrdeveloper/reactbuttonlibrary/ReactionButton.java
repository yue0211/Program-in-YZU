package com.amrdeveloper.reactbuttonlibrary;

import com.amrdeveloper.reactbutton.Reaction;
import com.example.chatroom.R;

public final class ReactionButton {

    public static Reaction defaultReact_smile = new Reaction(
            ReactConstants.DEFAULT,
            ReactConstants.DEFAULT,
            ReactConstants.GRAY,
            R.drawable.smile);

    public static Reaction defaultReact_love = new Reaction(
            ReactConstants.DEFAULT,
            ReactConstants.DEFAULT,
            ReactConstants.GRAY,
            R.drawable.love);

    public static Reaction defaultReact_cry = new Reaction(
            ReactConstants.DEFAULT,
            ReactConstants.DEFAULT,
            ReactConstants.GRAY,
            R.drawable.cry);

    public static Reaction defaultReact_angry = new Reaction(
            ReactConstants.DEFAULT,
            ReactConstants.DEFAULT,
            ReactConstants.GRAY,
            R.drawable.angry);

    public static Reaction defaultReact_nothing = new Reaction(
            ReactConstants.DEFAULT,
            ReactConstants.DEFAULT,
            ReactConstants.GRAY,
            R.drawable.nothing);

    public static Reaction defaultReact_good = new Reaction(
            ReactConstants.DEFAULT,
            ReactConstants.DEFAULT,
            ReactConstants.GRAY,
            R.drawable.good);


    public static Reaction[] reactions = {
            new Reaction(ReactConstants.DEFAULT, ReactConstants.GRAY, R.drawable.smile),
            new Reaction(ReactConstants.DEFAULT, ReactConstants.GRAY, R.drawable.love),
            new Reaction(ReactConstants.DEFAULT, ReactConstants.GRAY, R.drawable.cry),
            new Reaction(ReactConstants.DEFAULT, ReactConstants.GRAY, R.drawable.angry),
            new Reaction(ReactConstants.DEFAULT, ReactConstants.GRAY, R.drawable.nothing),
            new Reaction(ReactConstants.DEFAULT, ReactConstants.GRAY, R.drawable.good),
    };

}