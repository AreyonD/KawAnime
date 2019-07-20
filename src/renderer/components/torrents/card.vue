<template lang="pug">
  v-card.pa-2
    v-layout(row, wrap, column)
      v-tooltip(top, lazy, v-show='torrentName')
        .torrent-title.ellipsis.pt-1.pb-2(slot='activator') {{ torrentName }}
        span {{ torrentName }}

      v-divider

      v-flex(pl-4, pr-2, pb-0, d-flex, justify-space-between, align-center)
        v-progress-linear(v-model='progress', height='12', color='green')
        .progress-text {{ progress }}%

      v-flex(pt-0, pr-2, pb-2, d-flex, justify-end)
        .progress-text.time-remaining.grey--text.text-uppercase.text-xs-right {{ timeRemaining }}

      v-divider

      v-layout(justify-space-around, pl-4, pr-4)
        template(v-for='action in actions')
          v-btn(v-if='!action.displayInfo', icon, @click='action.action', large)
            v-icon(:color='action.color', large) {{ action.icon }}

        torrent-info(:torrent='torrent')
</template>

<script>
import moment from 'moment'

import TorrentInfo from '@/components/torrents/torrentInfo.vue'

export default {
  name: 'Torrent-Card',

  components: { TorrentInfo },

  props: ['torrent'],

  data: () => ({
    isPaused: false,
    creationDate: moment(),
    timeRemaining: ''
  }),

  computed: {
    torrentName () {
      return this.torrent.files && this.torrent.files.length
        ? this.torrent.files[0].name
        : undefined
    },
    progress () {
      return this.torrent
        ? (this.torrent.progress * 100).toFixed(2)
        : 0
    },
    actions () {
      return [{
        icon: this.isPaused ? 'play_arrow' : 'stop',
        color: '',
        action: () => this.actOnTorrent(this.isPaused ? 'resume' : 'pause')
      }, {
        icon: 'delete',
        color: 'red',
        action: this.stop
      }]
    }
  },

  methods: {
    stop () {
      this.actOnTorrent('pause')
      this.actOnTorrent('destroy')
    },
    setRemainingTime (torrent) {
      if (torrent.progress === 1) {
        this.timeRemaining = 'Done'
        return
      }

      this.timeRemaining = torrent.timeRemaining
        ? 'Ends ' + this.creationDate
          .clone()
          .add(torrent.timeRemaining)
          .fromNow()
        : 'Unknown time remaining...'
    },
    actOnTorrent (action) {
      this.$ipc.send(this.$eventsList.torrent.act.main, {
        magnet: this.torrent.magnetURI,
        action
      })

      if (action === 'pause') this.isPaused = true
      else if (action === 'resume') this.isPaused = false
    }
  },

  watch: {
    torrent (torrent) {
      this.setRemainingTime(torrent)
    }
  }
}
</script>

<style lang="stylus" scoped>
  .torrent-title
    font-size 18px
    font-weight 500
    letter-spacing 0.04em
    padding 0 12px

  .progress-text
    font-size 16px
    font-weight 300
    letter-spacing 0.02em
    padding 0 8px

  .time-remaining
    font-size 12px !important
</style>