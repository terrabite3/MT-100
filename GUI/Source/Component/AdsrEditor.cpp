

#include "AdsrEditor.h"

using namespace juce;


void AdsrEditor::EnvelopeData::drawDebugInformation(Graphics & g,
                                                    Rectangle<float> area) const
{
//    g.setColour(Colours::grey.withAlpha(0.5f));
//    area.setHeight(area.getHeight() / 5.0f);
//    
//    show(g, "AttackLevel", attackLevel, area);
//    show(g, "attackTime",  attackTime, area);
//    show(g, "decay",       decay, area);
//    show(g, "sustain",     sustain, area);
//    show(g, "release",     release, area);
}

void  AdsrEditor::EnvelopeData::show(Graphics & g,
                                     const String & title,
                                     float value,
                                     Rectangle<float> & area) const
{
    float halfWidth = area.getWidth() / 2.0f + 5.0f;
    
    g.drawText(title,
               area.withTrimmedRight(halfWidth),
               Justification::right, false);
    
    g.drawText(String(value),
               area.withTrimmedLeft(halfWidth),
               Justification::left, false);
    
    area.translate(0.0f, area.getHeight());
}



AdsrEditor::AdsrEditor()
{
    auto attack = segments.add(new Segment(this, nullptr));
    attack->setYAxisControls(false, true);
    
    auto retreat = segments.add(new Segment(this, attack));
    retreat->setYAxisControls(false, true);
    
    auto regroup = segments.add(new Segment(this, retreat));
    regroup->setYAxisControls(false, true);
    
    auto decay = segments.add(new Segment(this, regroup));
    decay->setYAxisControls(false, true);
    
    /* Sustain.  Y axis drag controls both left and right sides, which
     remain in step. */
    auto sustain = segments.add(new Segment(this, decay));
    sustain->setYAxisControls(true, true);
    sustain->setFixedDuration(0.5f);
    
    /* Release.  Y axis drag controls left hand sustain segment. */
    auto release = segments.add(new Segment(this, sustain));
    release->setYAxisControls(true, false);
    
    for (auto s: segments)
        addAndMakeVisible(s);
    
    /* Some initial data. */
    data = { 1.0f, 0.5f, 0.5f, 0.3f, 0.7f, 0.2f, 0.3f, 0.4f, 0.5f };
    
    /* Set the initial positions. */
    update();
}

void AdsrEditor::bindProperty(FilterEnvelopeProperty *prop)
{
    if (prop)
    {
        mTime1 = &prop->time1;
        mTime2 = &prop->time2;
        mTime3 = &prop->time3;
        mTime4 = &prop->time4;
        mTime5 = &prop->time5;
        mLevel1 = &prop->level1;
        mLevel2 = &prop->level2;
        mLevel3 = &prop->level3;
        mLevelSustain = &prop->levelSustain;
    }
    else
    {
        mTime1 = nullptr;
        mTime2 = nullptr;
        mTime3 = nullptr;
        mTime4 = nullptr;
        mTime5 = nullptr;
        mLevel1 = nullptr;
        mLevel2 = nullptr;
        mLevel3 = nullptr;
        mLevelSustain = nullptr;
    }
}

void AdsrEditor::refreshFromProperty()
{

    auto updateIfChangedLambda = [](IntProperty* prop, float& value)
    {
        if (prop)
            value = prop->value() / 100.f;
    };

    updateIfChangedLambda(mTime1, data.attackTime);
    updateIfChangedLambda(mTime2, data.retreatTime);
    updateIfChangedLambda(mTime3, data.regroupTime);
    updateIfChangedLambda(mTime4, data.decayTime);
    updateIfChangedLambda(mTime5, data.releaseTime);
    updateIfChangedLambda(mLevel1, data.attackLevel);
    updateIfChangedLambda(mLevel2, data.retreatLevel);
    updateIfChangedLambda(mLevel3, data.regroupLevel);
    updateIfChangedLambda(mLevelSustain, data.sustainLevel);

    update();
}

void AdsrEditor::resized()
{
    updateSegmentPositions();
}


void AdsrEditor::updateFromSegments()
{
    updateSegmentPositions();
    data.attackLevel    = segments[kAttack]->getRightLevel();
    data.attackTime     = segments[kAttack]->getDuration();
    data.retreatLevel   = segments[kRetreat]->getRightLevel();
    data.retreatTime    = segments[kRetreat]->getDuration();
    data.regroupLevel   = segments[kRegroup]->getRightLevel();
    data.regroupTime    = segments[kRegroup]->getDuration();
    data.decayTime      = segments[kDecay]->getDuration();
    data.sustainLevel   = segments[kSustain]->getLeftLevel();
    data.releaseTime    = segments[kRelease]->getDuration();
    
    notifyListeners();
}

void AdsrEditor::notifyListeners()
{
    auto updateIfChangedLambda = [](IntProperty* prop, float value)
    {
        if (prop && prop->value() != value * 100)
            prop->setValue(value * 100);
    };

    updateIfChangedLambda(mTime1, data.attackTime);
    updateIfChangedLambda(mTime2, data.retreatTime);
    updateIfChangedLambda(mTime3, data.regroupTime);
    updateIfChangedLambda(mTime4, data.decayTime);
    updateIfChangedLambda(mTime5, data.releaseTime);
    updateIfChangedLambda(mLevel1, data.attackLevel);
    updateIfChangedLambda(mLevel2, data.retreatLevel);
    updateIfChangedLambda(mLevel3, data.regroupLevel);
    updateIfChangedLambda(mLevelSustain, data.sustainLevel);
}

void AdsrEditor::updateSegmentPositions()
{
    float totalDuration = 0.0f;
    const float minDuration = 0.1f;
    
    for (auto s: segments)
        totalDuration += (s->getDuration() + minDuration);
    
    float width = getWidth();
    float height = getHeight();
    
    float xpos = 0.0f;
    
    for (auto s: segments)
    {
        float dur = s->getDuration();
        float pw = ((dur + minDuration) / totalDuration) * width;
        
        s->setBounds(int(xpos), 0, int(pw), height);
        
        xpos += int(pw);
    }
}

void AdsrEditor::update()
{
    segments[kAttack]->setRightLevel(data.attackLevel);
    segments[kAttack]->setDuration(data.attackTime);
    segments[kRetreat]->setRightLevel(data.retreatLevel);
    segments[kRetreat]->setDuration(data.retreatTime);
    segments[kRegroup]->setRightLevel(data.regroupLevel);
    segments[kRegroup]->setDuration(data.regroupTime);
    segments[kDecay]->setDuration(data.decayTime);
    segments[kSustain]->setLeftLevel(data.sustainLevel);
    segments[kRelease]->setDuration(data.releaseTime);
    
    updateSegmentPositions();
}


AdsrEditor::Segment::Segment(AdsrEditor * owner, AdsrEditor::Segment * segmentOnLeft)
:
owner(owner),
right(nullptr),
allowDurationChange(true)
{
    if (segmentOnLeft != nullptr)
        segmentOnLeft->right = this;
    
    left = segmentOnLeft;
}


void AdsrEditor::Segment::paint(Graphics & g)
{
    float height = (float) getHeight();
    float width = (float) getWidth();

    /** Pop some edges on our segment. */
    g.setColour(Colours::grey.withAlpha(0.5f));
    g.drawLine(width, 0.0f, width, height, 2.0f);
    g.drawLine(0.0f, 0.0f, 0.0f, height, 2.0f);

    /* Calculate the end positions. */
    float yleft = height - (float(leftLevel) * height);
    float yright = height - (float(rightLevel) * height);
    
    float ycurve = jmax(yleft, yright);
    
    /* Shade under our line. */
    {
        const Colour c1 = Colours::white.withAlpha(0.05f);
        const Colour c2 = Colours::white.withAlpha(0.2f);
        g.setGradientFill(ColourGradient(c2, 0.0, jmin(yleft, yright),
                                         c1, 0.0, height,
                                         false));
        Path p;
        p.startNewSubPath(0.0f, yleft);
        p.quadraticTo(width / 2.0, ycurve, width, yright);
        p.lineTo(width, height);
        p.lineTo(0.0, height);
        p.closeSubPath();
        
        g.fillPath(p);
    }
    
    /* And draw a nice solid line on top. */
    {
        g.setColour(Colours::white);
        
        Path p;
        p.startNewSubPath(0.0f, yleft);
        p.quadraticTo(width / 2.0, ycurve, width, yright);
        
        g.strokePath(p, PathStrokeType(4.0f));
    }
}


void AdsrEditor::Segment::setLeftLevel(float newLevel, ChainDirection direction)
{
    leftLevel = newLevel;
    
    if ((direction == kLeft || direction == kBoth) && left)
        left->setRightLevel(newLevel, kLeft);
    
    if ((direction == kRight || direction == kBoth) && leftRightLinked())
        setRightLevel(newLevel, kRight);
    
    repaint();
}

void AdsrEditor::Segment::setRightLevel(float newLevel, ChainDirection direction)
{
    rightLevel = newLevel;
    
    if ((direction == kRight || direction == kBoth) && right)
        right->setLeftLevel(newLevel, kRight);
    
    if ((direction == kLeft || direction == kBoth) && leftRightLinked())
        setLeftLevel(newLevel, kLeft);
    
    repaint();
}

void AdsrEditor::Segment::mouseDown(const MouseEvent & e)
{
    mouseDownData.left = leftLevel;
    mouseDownData.right = rightLevel;
    mouseDownData.duration = duration;
}

void AdsrEditor::Segment::mouseDrag(const MouseEvent & e)
{
    if (allowDurationChange)
    {
        float dx = float(e.getDistanceFromDragStartX()) / mouseSensitivity;
        duration = jlimit(0.0f, 1.0f, mouseDownData.duration + dx);
    }
    
    float dy = float(-1 * e.getDistanceFromDragStartY()) / mouseSensitivity;
    
    if (controllingLeft)
        setLeftLevel(jlimit(0.0f, 1.0f, mouseDownData.left + dy));
    else if (controllingRight)
        setRightLevel(jlimit(0.0f, 1.0f, mouseDownData.right + dy));
    
    owner->updateFromSegments();
}


void AdsrEditor::Segment::setYAxisControls(bool leftSide, bool rightSide)
{
    controllingLeft = leftSide;
    controllingRight = rightSide;
}
