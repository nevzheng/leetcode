// OA_13_favorite_genres
// Nevin Zheng
// 8/10/21

// https://github.com/Zhouzhiling/leetcode/blob/master/Amazon%20%20OA%202019%20%20Favorite%20Genres.md

/**
 Given a map Map<String, List<String>> userSongs with user names as keys and a
list of all the songs that the user has listened to as values.

Also given a map Map<String, List<String>> songGenres, with song genre as keys
and a list of all the songs within that genre as values. The song can only
belong to only one genre.

The task is to return a map Map<String, List<String>>, where the key is a user
name and the value is a list of the user's favorite genre(s). Favorite genre is
the most listened to genre. A user can have more than one favorite genre if
he/she has listened to the same number of songs per each of the genres.
 */

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

/**
 * First we index the genre of each song. O(numSongs) space and time
 * Then we use the index to count the frequency of each users song
 * then produce a summary of the top frequency genre
 * this takes O(totalSongs * map lookup time)
 *
 * There's an assumption about map complexity
 * if we get an ordered map then map lookup is O(1)
 * if its unordered its log(totalSongs)
 * @param user_songs
 * @param song_genres
 * @return
 */
map<string, vector<string>> favoriteGenres(
    const map<string, vector<string>>& user_songs,
    const map<string, vector<string>>& song_genres) {
  // Index the genera of each song
  // O(S) space and time, S = #songs
  map<string, string> genre_index;
  for (const auto& [genre, songs] : song_genres) {
    for (const auto& s : songs) genre_index.emplace(s, genre);
  }
  map<string, vector<string>> ans;
  // Use the index to query user's favorite genres
  // O(S_u) S_u = # songs across all users
  for (const auto& [user, songs] : user_songs) {
    map<string, int> freq;
    // Grab Song Genre, increment its freq
    for (const auto& s : songs) {
      if (auto it = genre_index.find(s); it != genre_index.end()) {
        ++freq[genre_index[s]];
      }
    }
    // Find the Max freq
    int max_freq = INT_MIN;
    for (const auto& it : freq) max_freq = max(max_freq, it.second);
    // Add any that have the top freq
    vector<string> v;
    for (auto [song, count] : freq)
      if (count > 0 and count == max_freq) v.push_back(song);
    std::sort(v.begin(), v.end());  // Sort for canonical form
    ans.emplace(user, v);           // Add User to list
  }
  return ans;
}

TEST_CASE("OA::13::1", "[oa13]") {
  map<string, vector<string>> user_songs = {
      {"David", {"song1", "song2", "song3", "song4", "song8"}},
      {"Emma", {"song5", "song6", "song7"}}};

  map<string, vector<string>> song_genres = {{"Rock", {"song1", "song3"}},
                                             {"Dubstep", {"song7"}},
                                             {"Techno", {"song2", "song4"}},
                                             {"Pop", {"song5", "song6"}},
                                             {"Jazz", {"song8", "song9"}}};

  map<string, vector<string>> favorites = {{"David", {"Rock", "Techno"}},
                                           {"Emma", {"Pop"}}};

  REQUIRE(favoriteGenres(user_songs, song_genres) == favorites);
}

TEST_CASE("OA::13::2", "[oa13]") {
  map<string, vector<string>> user_songs = {{"David", {"song1", "song2"}},
                                            {"Emma", {"song3", "song4"}}};

  map<string, vector<string>> song_genres = {};

  map<string, vector<string>> favorites = {{"David", {}}, {"Emma", {}}};

  REQUIRE(favoriteGenres(user_songs, song_genres) == favorites);
}