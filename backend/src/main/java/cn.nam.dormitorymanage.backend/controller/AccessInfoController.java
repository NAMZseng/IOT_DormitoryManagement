package cn.nam.dormitorymanage.backend.controller;

import cn.nam.dormitorymanage.backend.service.AccessInfoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

/**
 * @author Nanrong Zeng
 * @version 1.0
 */
@Controller
@RequestMapping("access")
public class AccessInfoController {

    @Autowired
    private AccessInfoService accessInfoService;

    /**
     * 学生出入宿舍楼权限判断
     * url示例:
     * http://49.232.57.160:8080/DormitoryManage/access/judgeAccess?buildingNum=9&cardNum=e0a01005
     *
     * @param buildingNum 宿舍楼号
     * @param studentNum  学生学号
     * @return 通过 1，拒绝 -1
     */
    @RequestMapping("judgeAccess")
    @ResponseBody
    public int judgeAccess(@RequestParam("buildingNum") int buildingNum, @RequestParam("cardNum") String cardNum) {

        return accessInfoService.judgeAccess(buildingNum, cardNum);
    }

    @RequestMapping("test")
    @ResponseBody
    public int test(@RequestParam("buildingNum") int buildingNum, @RequestParam("studentNum") int studentNum) {

        return buildingNum + studentNum;
    }
}
