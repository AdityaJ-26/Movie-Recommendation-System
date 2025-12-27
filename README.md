# **Movie Recommendation System**

A simple user preference based movie recommendation system created entirely in C language.<br>
<p>Generates movie recommendations based on user's watched movies list.<br>
  Uses user preferences generated from user's top attributes(actors, directors and genres).<br> 
  Rank movies using Jaccard Similarity by comparing movie attributes with user preferneces.<br>
  Give k top Scoring movies as recommendation.
</p>

## **Features**

- Multiple User Handling using randomly generated IDs.
- Password based user login authentication system.
- Persistent, updatable users and movies data storage using binary files(.dat).
- User preference based recommendation generation.

## **Working**

#### *Movies*
- Movies are managed through different admin level module(cannot be accessed by user), stored in .dat files and used for movies detail fetching.
- Movies have rating, name, actors, directors, genres as members.
- Attributes like genres, directors and actors are delimited using commas (,)

#### *User*
- Users are assigned randomly generated IDs, and have to setup password for login authentication.
- User can enter watched movie's names to their watch list.
- User data is stored in files with name as id.dat to store and access user files efficiently.

#### *Recommendation Generation*
- Uses user's watch list and movies file to get user's preferred attributes.
- Collects the top attributes and produce user preferences.
- Compares user preferences and movies attributes and generates scores using Jaccard Similarity and rating.
- Display top scored movies as recommendation.
