type range =
  | Today
  | Yesterday
  | MTD
  | Customer;

type option = {
    type_: range,
    label: string,
};

module RotatableButton = {
    let rangeOptions = [|
        {type_: Today, label: "Today"},
        {type_: Yesterday, label: "Yesterday"},
        {type_: MTD, label: "MTD"},
        {type_: Customer, label: "Customer Duration"}
    |];
    let onClick = (_event, ~currentRange={type_: Today, label: ""}, ~nextRange=_option=>()) => {
        let currentRangeIndex = rangeOptions |> Js.Array.findIndex((rangeOption) => {
            rangeOption.type_ == currentRange.type_
        });
        let nextRangeIndex = (currentRangeIndex + 1) mod (rangeOptions |> Array.length);
        nextRange(rangeOptions |. Array.get(nextRangeIndex));
    };
    let component = ReasonReact.statelessComponent("RotatableButton");
    let make = (~rangeOption={type_: Today, label: ""}, ~nextRange=(_option) => (), _children) => {
        ...component,
        render: _self => 
            <div onClick=((_event) => onClick(_event, ~currentRange=rangeOption, ~nextRange))>
                (rangeOption.label |> Utils.strEl)
            </div>
    };
};

type state = {
    button1: option
};

type action = 
  | UpdateButton1(option);

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
    ...component,
    initialState: () => {button1: {type_: Today, label: "Today"}},
    reducer: (action, _state) => 
        switch action {
        | UpdateButton1(option) => ReasonReact.Update({button1: option})
        },
    render: ({state, send}) => 
        <div>
            ("test" |> Utils.strEl)
            <RotatableButton 
                rangeOption=(state.button1)
                nextRange=(option => send(UpdateButton1(option)))
            />
        </div>
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));