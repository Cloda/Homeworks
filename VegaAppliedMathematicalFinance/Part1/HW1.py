from datetime import date

import QuantLib
import pandas


def makeException():
    raise ValueError("Not implemented")


class Calendar:
    def __init__(
        self,
        name: str = "US",
        market: str = "NYSE",
    ):
        if name == "US" and market == "NYSE":
            self.__implementation = QuantLib.UnitedStates(
                QuantLib.UnitedStates.NYSE
            )
        else:
            makeException()

    @staticmethod
    def getQuantlibDate(observationDate: date) -> QuantLib.Date:
        return QuantLib.Date(
            observationDate.day,
            observationDate.month,
            observationDate.year
        )

    @staticmethod
    def getPythonDate(observationDate: QuantLib.Date) -> date:
        return date(
            observationDate.year(),
            observationDate.month(),
            observationDate.dayOfMonth(),
        )

    def isBusinessDay(self, observationDate: date):
        return self.__implementation.isHoliday(
            self.getQuantlibDate(observationDate)
        )

    def advance(
        self,
        observationDate: date,
        shift: int,
    ):
        return self.getPythonDate(
            self.__implementation.advance(
                self.getQuantlibDate(observationDate),
                shift,
                QuantLib.Following,
                False
            )
        )

    def getNextBusinessDay(self, observationDate: date) -> date:
        shift = 1
        while not self.isBusinessDay(
            self.advance(observationDate, shift)
        ):
            shift += 1

        return self.advance(observationDate, shift)


class RatesCurveSet:
    # нужно научиться отдавать тип, ставку и на какой срок
    def __init__(self, curveSet: pandas.DataFrame):
        self.__curveSet = curveSet


class DiscreteDiscountingCurve:
    def __init__(
        self,
        paymentLag: str = "0D",
        rolling: str = "Following",
        dayCountConvention: str = "Act360",
        fixingOffSet: str = "2BD",
    ):
        if dayCountConvention != "Act360":
            makeException()

        self.__paymentLag = paymentLag
        self.__rolling = rolling
        self.__dayCountConvention = dayCountConvention
        self.__fixingOffSet = fixingOffSet

    def getValues(
        self,
        curveSet: RatesCurveSet
    ) -> (list[date], list[float]):
        return 1


class InterpolatedDiscountingCurve:
    def __init__(
        self,
        curve: DiscreteDiscountingCurve,
        calendar: Calendar,
        interpolationMethod: str = "LogDiscountFactors"
    ):
        self.__curve = curve
        self.__calendar = calendar
        self.__interpolationMethod = interpolationMethod
        if self.__interpolationMethod != "LogDiscountFactors":
            makeException()

    def getDiscountingFactor(
        self,
        observationDate: date,
        payDate: date
    ) -> float:
        return 1


data = pandas.DataFrame(
    {
        "Instrument_code": [
            "USD_3M_LIBOR", "USD_3M_LIBOR_3x6",
            "USD_3M_LIBOR_6x9", "USD_1Y_3M_LIBOR_1Y_FIX",
            "USD_2Y_3M_LIBOR_1Y_FIX", "USD_3Y_3M_LIBOR_1Y_FIX",
            "USD_4Y_3M_LIBOR_1Y_FIX", "USD_5Y_3M_LIBOR_1Y_FIX",
            "USD_6Y_3M_LIBOR_1Y_FIX", "USD_7Y_3M_LIBOR_1Y_FIX",
            "USD_8Y_3M_LIBOR_1Y_FIX", "USD_9Y_3M_LIBOR_1Y_FIX",
            "USD_10Y_3M_LIBOR_1Y_FIX", "USD_12Y_3M_LIBOR_1Y_FIX",
            "USD_15Y_3M_LIBOR_1Y_FIX", "USD_20Y_3M_LIBOR_1Y_FIX",
            "USD_25Y_3M_LIBOR_1Y_FIX", "USD_30Y_3M_LIBOR_1Y_FIX"
        ],
        "Quote": [
            0.3000, 0.7500, 1.1000, 0.9000, 1.3300, 1.5300, 1.6300,
            1.6900, 1.7300,
            1.7700, 1.8000, 1.8200, 1.8400, 1.8900, 1.9300, 1.9600,
            1.9500, 1.9200
        ],
        "Instrument_Type": [
            "Deposit", "FRA", "FRA", "IRS", "IRS", "IRS", "IRS",
            "IRS", "IRS",
            "IRS", "IRS", "IRS", "IRS", "IRS", "IRS", "IRS", "IRS",
            "IRS"
        ]
    }
)

valueDate = date(2022, 1, 31)
