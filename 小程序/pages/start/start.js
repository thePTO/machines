// start.js

Page({
    //跳转到图片识别的口令验证页面
    validate: function() {
        wx.navigateTo({
            url: '../wifi_station/index/index',
        })
    },


    change: function(e) {
        //当有输入时激活发送按钮，无输入则禁用按钮
        if (e.detail.value != "") {
            this.setData({
                threshold: e.detail.value,
                opacity: 1,
                disabled: false,
            })
        } else {
            this.setData({
                threshold: 0,
                opacity: 0.4,
                disabled: true,
            })
        }
    },

    /**
     * 生命周期函数--监听页面加载
     */
    onLoad: function(options) {

    },

    /**
     * 生命周期函数--监听页面初次渲染完成
     */
    onReady: function() {

    },

    /**
     * 生命周期函数--监听页面显示
     */
    onShow: function() {

    },

    /**
     * 生命周期函数--监听页面隐藏
     */
    onHide: function() {

    },

    /**
     * 生命周期函数--监听页面卸载
     */
    onUnload: function() {

    },

    /**
     * 页面相关事件处理函数--监听用户下拉动作
     */
    onPullDownRefresh: function() {

    },

    /**
     * 页面上拉触底事件的处理函数
     */
    onReachBottom: function() {

    },

    /**
     * 用户点击右上角分享
     */
    onShareAppMessage: function() {

    }
})