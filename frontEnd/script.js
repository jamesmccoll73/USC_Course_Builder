let input_date = "MW";
let time_begin = "12:00";
let time_beginZone = "pm"
let time_end = "8:00";
let time_endZone ="pm"
let className = "Bisc 225";

class Clock {
    constructor(index,tz){
         this.slots = ["","one","one30","two","two30","three","three30","four","four30","five","five30","six","six30","seven","seven30","eight","eight30","nine","nine30","ten","ten30","eleven","eleven30","twelve","twelve30"];
         this.currTime = parseInt(index);
         this.timeZone = tz;
    }
    current(){
        return this.slots[this.currTime] + this.timeZone;
    }
    update(){
        this.currTime +=1;
        if(this.currTime===23){
            this.timeZone="pm";
        }
        if(this.currTime>24){
            this.currTime=1;
        }
    }

}

const dateMap = {
    M:0,
    T:1,
    W:2,
    Th:3,
    F:4
};
const wordtoNum ={
    100: "one",
    130: "one30",
    200: "two",
    230: "two30",
    300: "three",
    330: "three30",
    400: "four",
    430: "four30",
    500: "five",
    530: "five30",
    600: "six",
    630: "six30",
    700: "seven",
    730: "seven30",
    800: "eight",
    830: "eight30",
    900: "nine",
    930: "nine30",
    1000: "ten",
    1030: "ten30",
    1100: "eleven",
    1130: "eleven30",
    1200: "twelve",
    1230: "twelve30"
};

time_begin= time_begin.replace(":","");
time_end= time_end.replace(":","");
let placeName = 0;
let bank = ["","one","one30","two","two30","three","three30","four","four30","five","five30","six","six30","seven","seven30","eight","eight30","nine","nine30","ten","ten30","eleven","eleven30","twelve","twelve30"];
let current_time=wordtoNum[time_begin]+time_beginZone;
let end_time=wordtoNum[time_end]+time_endZone;
for(let i =0;i<input_date.length;i++){
    placeName=0;
    let dayFill = dateMap[input_date[i]];
    let current_time=wordtoNum[time_begin]+time_beginZone;
    let startIndex = bank.indexOf(wordtoNum[time_begin]);
    const clock = new Clock(startIndex,time_beginZone);
    while(current_time!==end_time){
        let slotSelector= "#"+clock.current()
        console.log(slotSelector);
        const cells = document.querySelectorAll(slotSelector);
        console.log(slotSelector);
        fillCell(cells[dayFill],"blue");
        if(placeName===0){
            cells[dayFill].innerText = className;
            placeName++;
        }
        clock.update();
        current_time=clock.current();
        if(current_time===end_time){
            let slotSelector= "#"+clock.current()
            console.log(slotSelector);
            const cells = document.querySelectorAll(slotSelector);
            fillCell(cells[dayFill],"blue");
        }
    }

}

function fillCell(cell,color){
    cell.style.background = color;
}