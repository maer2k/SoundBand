#ifndef SYNC_H
#define SYNC_H
#include "song.h"
#include "node.h"
#include "LocalScanner.h"
#include <chrono>
#include "config.h"
#include "mysql.h"
#include <QMediaPlaylist>
#include "player.h"
#include "playlist.h"
#include "sync_global.h"

typedef std::chrono::time_point<std::chrono::high_resolution_clock> Clock;

class Node;


/**
 * @brief The Sync class is main class of this library.
 * the 'sync' has supported synced playning media files on network and saving media data into local database.
 */
class SYNCSHARED_EXPORT Sync : public QObject
{
    Q_OBJECT
private:
    Node *node;
    Player *player;
    PlayList *playList;
    QString lastUsedPlayList;
    QList<ETcpSocket*> servers;
    LocalScanner deepScaner;
    MySql *sql;
    int port;

    /**
     * @brief rescan - search for existing servers
     * result saved in servers
     */
    void rescan(bool deep = false);

    /**
     * @brief createPackage - Create a package that shows current state of the node
     * @param type - Type of an answer
     * @param pac - the resulting value
     * @return true if everything's done
     */
    bool createPackage(Type type , package& pac, milliseconds time = 0);

private slots:

    void clientSynced(ETcpSocket*);

    /**
     * @brief setSingle set singl or temp playlist
     * @return true if all done
     */
    bool setSingle(const SongStorage &media);

    /**
     * @brief updateSongs use method update avelable songs from sql database
     * @return true if all done
     */
    bool updateSongs(PlayList &list, const QString &playList = "");

    /**
     * @brief packageRender - the handler of all messages received.
     * @param socket
     */
    void packageRender(ETcpSocket* socket);

    /**
     * @brief deepScaned scaning in local network
     */
    void deepScaned(QList<ETcpSocket *> *);

    /**
     * @brief endPlay signal has ending playing
     */
    void endPlay(QMediaPlayer::State state);

public:

    /**
     * @brief getPlayListName
     * @return name of playlist
     */
    const QString& getPlayListName()const;

    /**
     * @brief repeat
     * @return flag of repeat
     */
    QMediaPlaylist::PlaybackMode repeat()const;

    /**
     * @brief setRepeat
     * @param flag new flag of repeat
     */
    void setRepeat(QMediaPlaylist::PlaybackMode flag);

    /**
     * @brief getSqlApi
     * @return pointer of sql api
     */
    MySql* getSqlApi();

    /**
     * @brief Play song in this device, if device has not supported playning media data this method throw MediaExcrption.
     * @param fbroadcast - server broadcasting sound.
     * @return true if all done else false.
     */
    bool play(bool fbroadcast = true);

    /**
     * @brief Play song in this device, if device has not supported playning media data this method throw MediaExcrption.
     * @param header of song
     * @param fbroadcast - server broadcasting sound.
     * @return true if all done else false.
     */
    bool play(const SongHeader &header,  bool fbroadcast = true);

    /**
     * @brief Play song in this device, if device has not supported playning media data this method throw MediaExcrption.
     * @param header of song
     * @param fbroadcast - server broadcasting sound.
     * @return true if all done else false.
     */
    bool play(const SongStorage &song,  bool fbroadcast = true);

    /**
     * @brief Play song in this device, if device has not supported playning media data this method throw MediaExcrption.
     * @param song playning media data.
     * @param fbroadcast - server broadcasting sound.
     * @return true if all done else false.
     */
    bool play(const Song &song, bool fbroadcast = true);
    /**
     * @brief Play song from local media file.
     * @param url of local media file.
     * @return true if all done else false.
     */
    bool play(QString url);
    /**
     * @brief Play song from local database by id.
     * @param id_song of song.
     * @param fbroadcast - server broadcasting sound.
     * @return true if all done else false.
     */
    bool play(int id_song, bool fbroadcast = true);
    /**
     * @brief Pause playning song.
     * state - state of playning
     */
    bool pause(bool state);
    /**
     * @brief stop playning song.
     */
    void stop();

    /**
     * @brief jump - jump to new position of playning media data.
     * @param seek - a new position of media data.
     */
    void jump(const qint64 seek);

    /**
     * @brief sync with server
     * @param sync - data of sync
     */
    bool sync(const Syncer& sync);

    /**
     * @brief isReadyToSync
     * @return true if node ready to sync;
     */
    bool isReadyToSync()const;

    /**
     * @brief sync with clients
     */
    void sync();

    /**
     * @brief sync with clients
     */
    void sync(ETcpSocket *socket);

    /**
     * @brief addNode add new connect
     * @param ip of connection
     * @param port of connection
     * @return true if all done
     */
    bool addNode(const QString ip, int port);

    /**
     * @brief scan - search for existing servers
     * result saved in servers
     */
    void scan();

    /**
     * @brief getServersList
     * @return  list of servers
     */
    const QList<ETcpSocket*>& getServersList() const;

    /**
     * @brief listen - a server
     * @param server - host
     * @return true id all done
     */
    bool listen(ETcpSocket* server);

    /**
     * @brief getVersion
     * @return current version of library
     */
    QString getVersion();

    /**
     * @brief setValume max valume is 100
     * @return true if all done
     */
    bool setValume(unsigned int value);

    /**
     * @brief getvalume
     * This property holds the current playback volume.
     * The playback volume is scaled linearly,
     *  ranging from 0 (silence) to 100 (full volume).
     *  Values outside this range will be clamped.
     */
    unsigned int getValume() const;

    /**
     * @brief seek
     * @return current playning milisecond
     */
    unsigned int seek()const;

    /**
     * @brief getPlayList
     * @return list of available songs
     */
    const QList<SongStorage> *getPlayList() const;

    /**
     * @brief SongHeader::getCurrentSongIndex
     * @return
     */
    int getCurrentSongIndex()const;

    /**
     * @brief getCurrentSong
     * @return playing song.
     */
    const SongStorage *getCurrentSong() const;

    /**
     * @brief getEndPoint
     * @return end point of playng song.
     */
    qint64 getEndPoint() const;

    /**
     * @brief addNewSong push a new song into local database.
     * @param name - name of pushed song
     * @return id of song.
     */
    int addNewSong(const QString &url);

    /**
     * @brief updatePlayList this method set a new playlist
     * @param id - id of playlist
     * @return true if all don
     */
    bool updatePlayList(const QString& _playList);

    /**
     * @brief next
     * @return true if all done;
     */
    bool next();

    /**
     * @brief prev
     * @return true if all done;
     */
    bool prev();

    /**
     * @brief playState
     * @return state of media data
     */
    QMediaPlayer::State playState()const;

    Sync(const QString &address = DEFAULT_ADRESS, int port = DEFAULT_PORT, const QString& datadir = DATABASE_NAME);
    ~Sync();

signals:
    /**
     * @brief seekChanged
     * @param seek
     * Signal the position of the content has changed to position,
     * expressed in milliseconds.
     */
    void seekChanged(qint64 seek);

    /**
     * @brief networkStateChange
     * signal if changed count of activity servers.
     */
    void networkStateChange();

    /**
     * @brief currentPlayListChanged
     * emited when added new songs into active playlist
     */
    void currentPlayListChanged();

    /**
     * @brief currentPlayListChanged
     * emited when selected a new playList
     */
    void selectedNewPlatList();

    /**
     * @brief currentSongChanged
     * emited when changed a playing song
     */
    void currentSongChanged();

    /**
     * @brief playStateChanged
     * emited when state of playing song changed
     */
    void playStateChanged();

};


#endif // SYNC_H
