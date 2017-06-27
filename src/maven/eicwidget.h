#ifndef PLOT_WIDGET_H
#define PLOT_WIDGET_H

#include "stable.h"
#include "mainwindow.h"
#include "line.h"
#include "barplot.h"
#include "boxplot.h"
#include "isotopeplot.h"
#include "point.h"
#include "plot_axes.h"


class PeakGroup;
class EIC;
class MainWindow;
class BarPlot;
class BoxPlot;
class IsotopePlot;
class Note;

class EicWidget : public QGraphicsView
{
    Q_OBJECT

public:
    EicWidget(QWidget *p);
    ~EicWidget();

    vector<EIC*> getEICs() { return eics; }
    vector<PeakGroup>& getPeakGroups() { return peakgroups; }
    PeakGroup* getSelectedGroup() 	  {  return &_selectedGroup; }
    mzSlice&   getMzSlice() 		  {	 return _slice; }
    QString eicToTextBuffer();


public slots:
    void setMzSlice(float mz);
    void setPPM(double ppm);
    void resetZoom();
    void zoom(float factor);
    void setMzRtWindow(float mzmin, float mzmax, float rtmin, float rtmax);
    void setMzSlice(const mzSlice& slice);

    void setRtWindow(float rtmin, float rtmax );
    void setSrmId(string srmId);
    void setPeakGroup(PeakGroup* group);
    void setCompound(Compound* c, Adduct* a);
    void setSelectedGroup(PeakGroup* group);
    void addEICLines(bool showSpline);
    void addCubicSpline();
    void addBaseLine();
    void addBaseline(PeakGroup* group);
    void addTicLine();
    void addMergedEIC();
    void setFocusLine(float rt);
    void drawSelectionLine(float rtmin,float rtmax);
    void addFocusLine(PeakGroup*);
    void addBarPlot(PeakGroup*);
    void addBoxPlot(PeakGroup*);
    void addIsotopicPlot(PeakGroup*);
    void addFitLine(PeakGroup*);
    void addMS2Events(float mzmin, float mzmax);
    void integrateRegion(float rtmin, float rtmax);
    void recompute();
    void replot(PeakGroup*);
    void replot();
    void replotForced();
    void print(QPaintDevice* printer);
    void showPeakArea(Peak*);
    void saveRetentionTime();
    void setGallaryToEics();

    void selectGroupNearRt(float rt);
    void eicToClipboard();

    void showSpline(bool f) { _showSpline=f; }
    void showPeaks(bool f)  { _showPeaks=f; }
    void showTicLine(bool f) { _showTicLine=f; }
    void showBicLine(bool f) { _showBicLine=f; }
    void showBaseLine(bool f) { _showBaseline=f; }
    void showNotes(bool f) { _showNotes=f; }
    void showMergedEIC(bool f) { _showMergedEIC=f; }
    void showEICLines(bool f) { _showEICLines=f; }
    void automaticPeakGrouping(bool f) { _groupPeaks=f; }
    void showMS2Events(bool f) { _showMS2Events=f; }


    void startAreaIntegration() { toggleAreaIntegration(true); }
    void startSpectralAveraging() { toggleSpectraAveraging(true); }
    void toggleAreaIntegration (bool f) { _areaIntegration=f; f ? setCursor(Qt::SizeHorCursor) : setCursor(Qt::ArrowCursor); }
    void toggleSpectraAveraging(bool f) { _spectraAveraging=f;f ? setCursor(Qt::SizeHorCursor) : setCursor(Qt::ArrowCursor); }


    void showIsotopePlot(bool f) { _showIsotopePlot=f; }
    void showBarPlot(bool f) { _showBarPlot=f; }
    void showBoxPlot(bool f) { _showBoxPlot=f; }

    void setStatusText(QString text);
    void autoZoom(bool f ) { _autoZoom=f; }

    void markGroupGood();
    void markGroupBad();
    void copyToClipboard();
    void selectionChangedAction();
    void freezeView(bool freeze);
protected:
    void moved(QMouseEvent *event);
    void selected(const QRect&);
    void wheelEvent(QWheelEvent *event);
    //void scaleView(qreal scaleFactor);
    void mouseReleaseEvent(QMouseEvent * mouseEvent);
    void mousePressEvent(QMouseEvent * mouseEvent);
    void mouseMoveEvent(QMouseEvent * mouseEvent);
    void mouseDoubleClickEvent ( QMouseEvent * event );
    void resizeEvent( QResizeEvent * ) { replot(NULL); }
    void contextMenuEvent(QContextMenuEvent * event);
    void keyPressEvent( QKeyEvent *e );
    void timerEvent ( QTimerEvent * event );

    void setupColors();
    void setTitle();
    void setScan(Scan*);
    void addAxes();
    void showAllPeaks();
    void addPeakPositions(PeakGroup* group);
    void createNotesTable();

signals:
    void viewSet(float,float,float,float);
    void scanChanged(Scan*);

private:

    mzSlice _slice;						// current slice
    float _focusLineRt;					// 0

    vector <EIC*> eics;					// vectors mass slices one from each sample
    deque  <EIC*> tics;					// vectors total chromatogram intensities;

    float _minX;						//plot bounds
    float _minY;
    float _maxX;
    float _maxY;
    float _zoomFactor;					//scaling of zoom in

    QPointF _lastClickPos;
    QPointF _mouseStartPos;
    QPointF _mouseEndPos;

    BarPlot* _barplot;
    BoxPlot* _boxplot;
    IsotopePlot* _isotopeplot;
    Note* _statusText;

    bool _showSpline;
    bool _showBaseline;
    bool _showTicLine;
    bool _showBicLine;
    bool _showMergedEIC;
    bool _showNotes;
    bool _showPeaks;
    bool _showEICLines;
    bool _autoZoom;
    bool _groupPeaks;
    bool _showMS2Events;

    bool _areaIntegration;
    bool _spectraAveraging;

    bool _showIsotopePlot;
    bool _showBarPlot;
    bool _showBoxPlot;

    bool _frozen;
    int _freezeTime;
    int _timerId;



    vector<PeakGroup> peakgroups;	    //peaks grouped across samples
    PeakGroup  _selectedGroup;			//currently selected peak group
	PeakGroup  _integratedGroup;		//manually integrated peak group
    
    //gui related
    QWidget *parent;
    QGraphicsLineItem* _focusLine;
    QGraphicsLineItem* _selectionLine;

    void showPeak(float freq, float amplitude);
    void groupPeaks();
    void computeEICs();
    void cleanup();		//deallocate eics, fragments, peaks, peakgroups
    void clearPlot();	//removes non permenent graphics objects
    void findPlotBounds(); //find _minX, _maxX...etc
    mzSlice visibleSamplesBounds(); //find absoulte max and min for visible samples
    mzSlice visibleEICBounds(); //find absolute min and max for extracted ion chromatograms

    float toX(float x);
    float toY(float y);
    float invX(float x);
    float invY(float y);


    MainWindow* getMainWindow();		//return parent 
    void zoomPeakGroup( PeakGroup* group );

};


#endif
