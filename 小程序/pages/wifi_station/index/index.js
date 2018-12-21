//index.js
//获取应用实例
const app = getApp()

Page({
    onLoad: function() {
        //从oneNET请求我们的Wi-Fi气象站的数据
      var devicesId = "503131920" // 填写在OneNet上获得的devicesId 形式就是一串数字 例子:9939133
      var api_key = "JLtZ4wtqKd8jCmJ6HZhPJPKmHs8=" // 填写在OneNet上的 api-key 例子: VeFI0HZ44Qn5dZO14AuLbWSlSlI=
        const requestTask = wx.request({
          url: 'https://api.heclouds.com/devices/' + devicesId + '/datapoints?datastream_id=Light,Temperature,Humidity&limit=15',
          header: {
            'content-type': 'application/json',
            'api-key': api_key
          },
          success: function (res) {
            var app = getApp()
            app.globalData.temperature = res.data.data.datastreams[0]
            app.globalData.light = res.data.data.datastreams[1]
            app.globalData.humidity = res.data.data.datastreams[2]
            console.log(app.globalData.light)
            //跳转到天气页面，根据拿到的数据绘图
            wx.navigateTo({
              url: '../tianqi/tianqi',
            })
          },

          fail: function (res) {
            console.log("fail!!!")
          },

          complete: function (res) {
            console.log("end")
          }
        })
    }
})